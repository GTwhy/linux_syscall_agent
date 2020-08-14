#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaphore_helper.h"

#define FTOK_FILE "/home/lsca"
#define STR_LEN 32
#define SHM_SIZE 256

int main(void)
{
    int semid, shmid;
    char buf[STR_LEN] = {0};
    void *pshm_addr = NULL;
    shm_t * pshm = NULL;
    int i = 0;

/*获取信号量标识符*/    
    semid = creat_sem( );
    if(semid == -1)
    {    printf("%s : semid = %d!\n", __func__, semid);
        return -1;
    }

/*获取共享内存标识符*/
    shmid = shmget(ftok(FTOK_FILE,111), sizeof(shm_t), IPC_CREAT|0666);
    if(shmid == -1)
    {
        printf("%s: shmid = %d!\n", __func__, shmid);
        return -1;
    }

/*当前进程连接该共享内存段*/
    pshm_addr = shmat(shmid, 0, 0);
    if(pshm_addr == (void *)-1)
    {
        printf("%s : pshm_addr = (void*)-1!\n",__func__);
        return -1;
    }

    pshm = pshm_addr;
printf("read process : semid is %d, shmid is %d!\n",semid, shmid);

    for(; ;)
    {
/*占用信号量，p操作*/        
        if(sem_p(semid))
        {
            printf("%s : sem_p failed !\n",__func__);
            return -1;
        }
        
        printf("enter write process!\n");    
        printf("enter something, end with end >\n");
        fgets(buf, STR_LEN, stdin);
        pshm->num = i++;
        strcpy(pshm->buf, buf);        
        printf("leave write process!\n\n");

/*释放信号量，v操作*/        
        if(sem_v(semid))
        {
            printf("%s : sem_v failed!\n",__func__);
            return -1;
        }

        if(!strncmp(pshm->buf , "end", 3))
            break;
        
        sleep(2);
    }

/*进程和共享内存脱离*/
    if(shmdt(pshm_addr) == -1)
    {
        printf("%s : shmdt is failed!\n",__func__);
        return -1;
    }
    
    printf(" Good Bye! \n");
    return 0;

}

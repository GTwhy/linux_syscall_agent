#include "daemon.h"

int main(void)
{
    int semid,shmid;
    char buf[STR_LEN] = {0};
    int i = 0;
    void *pshm_addr = NULL;
    shm_t *pshm = NULL;

/*获取信号量标识符*/    
    semid = creat_sem( );
    if(semid == -1)
    {    printf("%s : semid = %d!\n", __func__, semid);
        return -1;
    }

/*创建信号量之后的，初始化操作*/        
    if(set_semvalue(semid))
    {
        printf("%s : set_semvalue failed!\n",__func__);
        return -1;
    }

/*获取共享内存标识符*/
    shmid = shmget(ftok(FTOK_FILE, 111), sizeof(shm_t), IPC_CREAT|0666);
    if(shmid == -1)
    {
        printf("%s : shmid = %d!\n",__func__, shmid);
        return -1;
    }

/*当前进程连接该共享内存段*/
    pshm_addr =(void*)shmat(shmid, 0 , 0);
    if(pshm_addr == (void *)-1)
    {
        printf("%s : pshm_addr == (void*)0!\n",__func__);
        return -1;
    }

    pshm = pshm_addr;
    printf("read process semid is %d,shmid is %d!\n", semid,shmid);

/*让写数据的进程先运行*/    
    sleep(4);
    for(; ;)
    {
/*占用信号量，p操作*/    
        if(sem_p(semid))
        {
            printf("%s : sem_p failed !\n",__func__);
            return -1;
        }
        
        printf("enter read process!\n");
        printf("pshm->num is %d!\n",pshm->num);
        printf("pshm->buf is %s", pshm->buf);
        printf("leave read process!\n\n");

/*释放信号量，v操作*/                    
        if(sem_v(semid))
        {
            printf("%s : sem_v failed!\n",__func__);
            return -1;
        }

        if(!strncmp(pshm->buf, "end", 3))
            break;
	usleep(100000);
    }

/*删除信号量*/
    if(del_sem(semid))
    {
        printf("%s : del_sem failed!\n", __func__);
        return -1;
    }

/*进程和共享内存脱离*/
    if(shmdt(pshm_addr) == -1)
    {
        printf("%s : shmdt failed!\n",__func__);
        return -1;
    }

/*删除共享内存*/
    if(shmctl(shmid, IPC_RMID, 0) == -1)
    {
        printf("%s : shmctl failed!\n",__func__);
        return -1;
    }

    printf("BYE!\n");
    return 0;

}

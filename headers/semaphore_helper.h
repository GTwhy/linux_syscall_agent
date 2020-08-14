#ifndef LSCA_SEMAPHORE_HELPER_H
#define LSCA_SEMAPHORE_HELPER_H

#define FTOK_FILE_SEMAPHORE "/etc/group"

int creat_sem(void);
int set_semvalue(int semid);
int sem_p(int semid);
int sem_v(int semid);
int del_sem(int semid);

union semun;

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


#endif //LSCA_SEMAPHORE_HELPER_H

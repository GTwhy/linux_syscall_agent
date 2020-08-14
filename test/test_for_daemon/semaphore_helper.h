#ifndef _SEMAPHORE_HELPER_H_
#define _SEMAPHORE_HELPER_H_

#include "daemon.h"

#define FTOK_FILE "/home/lsca"

int creat_sem(void);
int set_semvalue(int semid);
int sem_p(int semid);
int sem_v(int semid);
int del_sem(int semid);

#endif

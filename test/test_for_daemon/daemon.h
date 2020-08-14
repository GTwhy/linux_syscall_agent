#ifndef __DAEMON_H_
#define __DAEMON_H_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaphore_helper.h"

#define STR_LEN 32
#define SHM_SIZE 256
#define FTOK_FILE "/home/lsca"


union semun;
struct _tag_shm;


union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

typedef struct _tag_shm
{
    char buf[SHM_SIZE];
    unsigned short num;
}shm_t;

#endif

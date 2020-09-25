#include "../headers/syscall_agent_write_read.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/**
 *
 * @param task
 * @return
 */
int agent_write(Node* task){
    int res;
    res = write(atoi(task->x0),task->x1,atoi(task->x2));
    printf("agenting\n");
    return res;
}

int agent_read(Node* task){
    return 888;
}
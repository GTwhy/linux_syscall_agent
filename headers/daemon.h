#ifndef LSCA_DAEMON_H
#define LSCA_DAEMON_H

#include <sys/types.h>

#define REG_SIZE 32 //模拟寄存器大小
#define STACK_SIZE 64 //模拟栈大小
#define SYSCALL_AGENT_MAX 1024 //系统调用代理数量
#define RESULT_BUFFER_SIZE 16 //结果缓冲区大小
#define RING_BUFFER_SIZE 16 //RingBuffer 的 Node数量


int daemon_exit();


#endif //LSCA_DAEMON_H

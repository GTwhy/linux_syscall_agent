#ifndef LSCA_RING_BUFFER_H
#define LSCA_RING_BUFFER_H

#include <stddef.h>
#include "daemon.h"
#include <sys/types.h>

#define FTOK_FILE_BUFFER "/etc/profile"
/**
 * 共享内存队列的队列节点
 * 用于传递
 */
typedef struct queue_node
{
    int syscall_number;
    int res_buf_number;
    char x0[REG_SIZE];
    char x1[REG_SIZE];
    char x2[REG_SIZE];
    char stack[STACK_SIZE];
}Node;

/**
 * 传递返回值
 */
typedef struct result_node
{
    char get_result_flag;
    char taken_flag;
    int x0;
    char stack[STACK_SIZE];
}Result;

/**
 * 环形队列缓冲区
 */
typedef struct ring_buffer
{
    Node queue[RING_BUFFER_SIZE];
    Result res_buf[RESULT_BUFFER_SIZE];
    int head;
    int tail;
    int size;
    int res_buf_pointer;
}RingBuffer;
Node queue_front2(RingBuffer* buf);

RingBuffer* init_buffer(int number_of_nodes);
void* buffer_malloc(size_t size);
int delete_shm(RingBuffer* buf);
int is_buffer_empty(RingBuffer* buf);
int is_buffer_full(RingBuffer* buf);
int en_queue(RingBuffer* buf, Node val);
int de_queue(RingBuffer* buf);
Node* queue_front(RingBuffer* buf);
Node* queue_rear(RingBuffer* buf);
int lock_shm();
int unlock_shm();
void return_value_to_user(RingBuffer* buf, int res_buf_num, int res_val);
int del_task(RingBuffer* buf);
void return_buffer_to_user(Node* node,void *res_buf);


#endif //LSCA_RING_BUFFER_H

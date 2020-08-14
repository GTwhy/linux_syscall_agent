//
// Created by why on 2020/8/7.
//

#ifndef LSCA_RING_BUFFER_H
#define LSCA_RING_BUFFER_H

#define BUF_SIZE 256
#define STACK_SIZE 1024


/**
 * 共享内存队列的队列节点
 * 用于传递
 */
typedef struct queue_node
{
    char syscall_number;
    char task_id[4]; //采用函数名+time的字符串经过SHA-256运算后得到的消息验证码作为唯一标识符
    char finish_flag;
    char x0[BUF_SIZE];
    char x1[BUF_SIZE];
    char x2[BUF_SIZE];
    char x3[BUF_SIZE];
    char x4[BUF_SIZE];
    char x5[BUF_SIZE];
    char x6[BUF_SIZE];
    char x7[BUF_SIZE];
    char stack [STACK_SIZE];
}Node;

typedef struct ring_buffer
{
    Node* queue;
    int head;
    int tail;
    int size;
}RingBuffer;



RingBuffer* bufferInit(int number_of_nodes);
int isBufferEmpty(RingBuffer* buf);
int isBufferFull(RingBuffer* buf);
int enQueue(RingBuffer* buf, Node val);
int deQueue(RingBuffer* buf);
Node* queueFront(RingBuffer* buf);
Node* queueRear(RingBuffer* buf);
void bufferFree(RingBuffer* buf);




#endif //LSCA_RING_BUFFER_H

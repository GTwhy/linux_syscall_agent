
#include "ring_buffer.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

/** Initialize your data structure here. Set the size of the queue to be k. */
RingBuffer* bufferInit(int number_of_nodes) {
    RingBuffer* buf = malloc(sizeof(RingBuffer));
    buf->queue = malloc(number_of_nodes*sizeof(Node));
    buf->head = -1;
    buf->tail = -1;
    buf->size = number_of_nodes;
    memset((void*)buf->queue,0, number_of_nodes*sizeof(Node));
    return buf;
}


int isBufferEmpty(RingBuffer* buf){
    return (buf->head == -1);
}

int isBufferFull(RingBuffer* buf){
    return ((buf->tail+1)%buf->size == buf->head);
}

int enQueue(RingBuffer* buf, Node val){
    if(isBufferFull(buf)){
        printf("Buffer is full");
        return 0;
    }
    if(isBufferEmpty(buf)){
        buf->head = 0;
    }
    buf->tail = (buf->tail+1)%buf->size;
    buf->queue[buf->tail] = val;
    return 1;
}

int deQueue(RingBuffer* buf){
    if(isBufferEmpty(buf)){
        printf("deQueue failed : Buffer is empty\n");
        return 0;
    }
    //TODO:清理
    memset((void*)&buf->queue[buf->head],0,sizeof(Node));
    if (buf->tail == buf->head){
        buf->head = -1;
        buf->tail = -1;
        return 1;
    }
    buf->head = (buf->head+1)%buf->size;
    return 1;
}

Node* queueFront(RingBuffer* buf){
    if(isBufferEmpty(buf)){
        printf("get queueFront failed : Buffer is empty\n");
        return NULL;
    }
    return &buf->queue[buf->head];
}

Node* queueRear(RingBuffer* buf){
    if(isBufferEmpty(buf)){
        printf("get queueRear failed : Buffer is empty\n");
        return NULL;
    }
    return &buf->queue[buf->tail];
}

void bufferFree(RingBuffer* buf){
    free(buf->queue);
    free(buf);
}

int main(){
    RingBuffer* buf;
    buf = bufferInit(10);
    Node n;
    void *s = "hello";
    memcpy((void*)n.x0,s,strlen(s));
    //TODO: enqueue的节点需要初始化
    enQueue(buf,n);
    s = "123";
    memcpy((void*)n.x1,s,strlen(s));
    enQueue(buf,n);
    printf("Head %s  %d\n", queueFront(buf)->x0, atoi(queueFront(buf)->x2));
    printf("Rear %s  %d\n", queueRear(buf)->x0, atoi(queueRear(buf)->x1));
    deQueue(buf);
    printf("Head %s  %d\n", queueFront(buf)->x0, atoi(queueFront(buf)->x1));
    return 0;
}
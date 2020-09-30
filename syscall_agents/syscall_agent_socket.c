//
// Created by why on 2020/9/27.
//
#include "../headers/syscall_agent_socket.h"
#include "../headers/ring_buffer.h"
#include "../headers/lsca_syscall.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int agent_socket(Node* task)
{
    int res = 666;
    res = socket(atoi(task->x0),atoi(task->x1),atoi(task->x2));
    return res;
}

int agent_bind(Node* task)
{
    int res = 666;
    int connfd;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    memcpy(&addr,task->x1,sizeof(addr));
    //res = bind(atoi(task->x0),&addr,atoi(task->x2));

    //test
//    addr.sin_family=AF_INET;
//    addr.sin_addr.s_addr=htonl(INADDR_ANY);
//    addr.sin_port=htons(12345);
//    printf("%d \n",addr);
    res = bind(atoi(task->x0),(struct sockaddr *)&addr,sizeof(addr));
    return res;
}

int agent_connect(Node* task)
{
    int res = 666;
    int connfd;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    memcpy(&addr,task->x1,sizeof(addr));
    res = connect(atoi(task->x0),(struct sockaddr *)&addr,atoi(task->x2));
    return res;
}


int agent_listen(Node* task)
{
    int res = 666;
    res = listen(atoi(task->x0),atoi(task->x1));
    return res;
}


int agent_accept(Node* task)
{
    int res = 666;
    //TODO:不需sockaddr_in 记录请求方信息则可以后面两个变量填写NULL，前期方便测试先NULL，后期改
    res = accept(atoi(task->x0),NULL,NULL);
    return res;
}
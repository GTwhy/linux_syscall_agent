////#include "../headers/syscall_wrapper_socket.h"
//#include "../headers/ring_buffer.h"
//#include "../headers/lib.h"
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//
//int socket(int a, int b, int c)
//{
//    if(buf_addr == NULL){
//        buf_addr = buffer_malloc(sizeof(RingBuffer));
//    }
//    int res;
//    //将参数封装进用于传递参数的数据结构
//    Node node;
//    void* pa = node.x0;
//    void* pb = node.x1;
//    void* pc = node.x2;
//    node.syscall_number = __NR_socket;
//    sprintf(pa, " %d" , a);
//    sprintf(pb, " %d" , b);
//    sprintf(pc, " %d" , c);
//    res = agent_syscall(node);
//    res = get_res(res);
//    return res;
//}
//
//int bind(int a, int b, int c)
//{
//    if(buf_addr == NULL){
//        buf_addr = buffer_malloc(sizeof(RingBuffer));
//    }
//    int res;
//    //将参数封装进用于传递参数的数据结构
//    Node node;
//    void* pa = node.x0;
//    void* pb = node.x1;
//    void* pc = node.x2;
//    node.syscall_number = __NR_bind;
//    sprintf(pa, " %d" , a);
//    sprintf(pc, " %d" , c);
//    strcpy(pb,b);
//    res = agent_syscall(node);
//    res = get_res(res);
//    return res;
//}
//
//int listen(int a, int b)
//{
//    if(buf_addr == NULL){
//        buf_addr = buffer_malloc(sizeof(RingBuffer));
//    }
//    int res;
//    //将参数封装进用于传递参数的数据结构
//    Node node;
//    void* pa = node.x0;
//    void* pb = node.x1;
//    node.syscall_number = __NR_listen;
//    sprintf(pa, " %d" , a);
//    sprintf(pb, " %d" , b);
//    res = agent_syscall(node);
//    res = get_res(res);
//    return res;
//}
//int accept(int a, int b, int c)
//{
//    if(buf_addr == NULL){
//        buf_addr = buffer_malloc(sizeof(RingBuffer));
//    }
//    int res;
//    //将参数封装进用于传递参数的数据结构
//    Node node;
//    void* pa = node.x0;
//    void* pb = node.x1;
//    void* pc = node.x2;
//    node.syscall_number = __NR_accept;
//    sprintf(pa, " %d" , a);
//    sprintf(pc, " %d" , c);
//    strcpy(pb,b);
//    res = agent_syscall(node);
//    res = get_res(res);
//    return res;
//}

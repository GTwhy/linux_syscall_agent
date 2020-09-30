#include "../headers/syscall_wrapper_socket.h"
#include "../headers/ring_buffer.h"
#include "../headers/lsca_syscall.h"
#include "../headers/lib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 获得一个socketfd
 * @param a
 * @param b
 * @param c
 * @return
 */
int socket(int a, int b, int c)
{
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pb = node.x1;
    void* pc = node.x2;
    node.syscall_number = __NR_socket;
    sprintf(pa, " %d" , a);
    sprintf(pb, " %d" , b);
    sprintf(pc, " %d" , c);
    res = agent_syscall(node);
    res = get_res(res);
    return res;
}

/**
 * 将socketfd与ip和端口绑定
 * @param a socketfd
 * @param b adder结构体，需要打包传送16字节大小
 * @param c 可以直接sizeof
 * @return 失败返回-1
 */
int bind(int a, struct sockaddr *b, int c)
{
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pb = node.x1;
    void* pc = node.x2;
    node.syscall_number = __NR_bind;
    sprintf(pa, " %d" , a);
    sprintf(pc, " %d" , c);
    memset(pb,0,16);
    memcpy(pb,b,sizeof(struct sockaddr));
    res = agent_syscall(node);
    res = get_res(res);
    return res;
}
/**
 * 连接server
 * @param a socketfd
 * @param b sockaddr
 * @param c sizeof sockaddr
 * @return
 */
int connect(int a, struct sockaddr *b, int c)
{
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pb = node.x1;
    void* pc = node.x2;
    node.syscall_number = __NR_connect;
    sprintf(pa, " %d" , a);
    sprintf(pc, " %d" , c);
    memset(pb,0,16);
    memcpy(pb,b,sizeof(struct sockaddr));
    res = agent_syscall(node);
    res = get_res(res);
    return res;
}


/**
 * listen指定端口收到的消息
 * @param a socketfd
 * @param b 缓冲队列大小
 * @return
 */
int listen(int a, int b)
{
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pb = node.x1;
    node.syscall_number = __NR_listen;
    sprintf(pa, " %d" , a);
    sprintf(pb, " %d" , b);
    res = agent_syscall(node);
    res = get_res(res);
    return res;
}

/**
 *
 * @param a 用于监听的socketfd
 * @param b 指向本地socketaddr_in结构体的指针，用于存储调用connect的主机信息，从哪个ip:port来，不需要直接填NULL即可，需要的话需要开辟空间
 * @param c addrlen，可以采用sizeof(addr)
 * @return 成功则返回新的socketfd用于sned()和recv()，失败返回-1
 */
int accept(int a, void *b, int *c)
{
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pb = node.x1;
    void* pc = node.x2;
    node.syscall_number = __NR_accept;
    sprintf(pa, " %d" , a);
    //memcpy(pc,c,32);
    //memcpy(pb,b,32);
    res = agent_syscall(node);
    res = get_res(res);
    return res;
}

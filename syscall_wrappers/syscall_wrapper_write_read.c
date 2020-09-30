#include "../headers/syscall_wrapper_write_read.h"
#include "../headers/ring_buffer.h"
#include "../headers/lsca_syscall.h"
#include "../headers/lib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern char res_buf[64];
//TODO：移植过来
//重新定义write库函数的包装
/**
 * write库函数的包装函数，由于涉及到输出终端的设置，目前还没有根据客户端程序的终端做重定向
 * 因此需要将daemon和客户程序运行在同一终端下。
 * @param a 第一个参数，以下类推。
 * @param b
 * @param c
 * @return
 */
ssize_t write(int fd, void *buf, size_t count)
{
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pb = node.x1;
    void* pc = node.x2;
    node.syscall_number = __NR_write;
    sprintf(pa, " %d" , fd);
    sprintf(pc, " %ld" , count);
    //TODO:后续应替换为memcpy更加通用
    memcpy(pb,buf,32);
    res = agent_syscall(node);
    res = get_res(res);
    return res;
}



//重新定义read库函数的包装
/**
 * read库函数的包装函数，由于涉及到输出终端的设置，目前还没有根据客户端程序的终端做重定向
 * 因此需要将daemon和客户程序运行在同一终端下。
 * @param a 第一个参数，以下类推。
 * @param b
 * @param c
 * @return
 */
ssize_t read(int fd, void * buf, size_t count)
{
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pc = node.x2;
    node.syscall_number = __NR_read;
    sprintf(pa, " %d" , fd);
    sprintf(pc, " %ld" , count);
    res = agent_syscall(node);
    res = get_res_with_buffer(res,buf);
//    //读到了东西，存在stack中，需要取出，这里有个潜在bug：结果缓冲区先
//    if(res>=0){
//        //拷贝缓冲区，可以用memcpy拷贝指定大小的数据，或使用strcoy拷贝/0之前的字符数据
//        memcpy(buf,read_buf,32);
//    }
    return res;
}

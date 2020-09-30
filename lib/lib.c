#include <stdlib.h>
#include "../headers/semaphore_helper.h"
#include "../headers/ring_buffer.h"
#include "../headers/lib.h"
#include "../headers/syscall_wrapper_write_read.h"
#include "../headers/syscall_wrapper_socket.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

static RingBuffer* buf_addr = NULL;
char res_buf[64];
/**
 * 封装系统调用代理函数供lib使用
 * @param node
 * @return
 */
int agent_syscall(Node node){
    if(buf_addr == NULL){
        buf_addr = buffer_malloc(sizeof(RingBuffer));
    }
    //TODO:添加错误处理，多线程改进
    int res_num;
    while (lock_shm());
    res_num = en_queue(buf_addr,node);
    if(res_num < 0){
        printf("%s en_queue failed!\n",__func__);
    }
    while (unlock_shm());
    return res_num;
}


int get_res(int res_num){
    //TODO:后续添加多线程可重入改进
    int res;
    for(;;){
        //TODO:&&的运行顺序需要检验，否则可能导致错误
        if(!lock_shm()){
            if(buf_addr->res_buf[res_num].get_result_flag == 1){
                buf_addr->res_buf[res_num].get_result_flag = 0;
                res = buf_addr->res_buf[res_num].x0;
                //从结果缓冲区中复制传递的数据，再解除占用。
                memcpy(res_buf,buf_addr->res_buf[res_num].stack,32);
                buf_addr->res_buf[res_num].taken_flag = 0;
                de_queue(buf_addr);
                while (unlock_shm());
                return res;
            }
        }
        while (unlock_shm());
    }
}

int get_res_with_buffer(int res_num,char *buf_ptr){
    //TODO:后续添加多线程可重入改进
    int res;
    for(;;){
        //TODO:&&的运行顺序需要检验，否则可能导致错误
        if(!lock_shm()){
            if(buf_addr->res_buf[res_num].get_result_flag == 1){
                buf_addr->res_buf[res_num].get_result_flag = 0;
                res = buf_addr->res_buf[res_num].x0;
                //从结果缓冲区中复制传递的数据，再解除占用。
                memcpy(buf_ptr,buf_addr->res_buf[res_num].stack, STACK_SIZE);
                buf_addr->res_buf[res_num].taken_flag = 0;
                de_queue(buf_addr);
                while (unlock_shm());
                return res;
            }
        }
        while (unlock_shm());
    }
}

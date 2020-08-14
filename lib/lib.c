#include <stdlib.h>
#include "../headers/semaphore_helper.h"
#include "../headers/ring_buffer.h"
#include "../headers/lib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

static RingBuffer* buf_addr =NULL;

/**
 * 封装系统调用代理函数供lib使用
 * @param node
 * @return
 */
int agent_syscall(Node node){
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
                res = buf_addr->res_buf[res_num].x0;
                buf_addr->res_buf[res_num].taken_flag = 0;
                while (unlock_shm());
                return res;
            }
        }
        while (unlock_shm());
    }
}

/**
 * 重新定义write库函数的包装，后续移到wrapper文件中
 * @param a
 * @param b
 * @param c
 * @return
 */

int write(int a, char* b, int c){
    if(buf_addr == NULL){
        buf_addr = buffer_malloc(sizeof(RingBuffer));
    }
    int res;
    //将参数封装进用于传递参数的数据结构
    Node node;
    void* pa = node.x0;
    void* pb = node.x1;
    void* pc = node.x2;
    node.syscall_number = __NR_write;
    sprintf(pa, " %d" , a);
    sprintf(pc, " %d" , c);
    strcpy(pb,b);
    res = agent_syscall(node);
    res = get_res(res);
    return res;
}



//重新定义read库函数的包装
int read(int a, char* b, int c){

}



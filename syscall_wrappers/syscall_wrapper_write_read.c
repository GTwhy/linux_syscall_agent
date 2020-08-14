#include "../headers/syscall_wrapper_write_read.h"
//TODO：移植过来
////重新定义write库函数的包装
//int write(int a, char* b, int c){
//    if(buf_addr == NULL){
//        buf_addr = buffer_malloc(sizeof(RingBuffer));
//    }
//    int res;
//    //将参数封装进用于传递参数的数据结构
//    Node node;
//    void* pa = node.x0;
//    void* pb = node.x1;
//    void* pc = node.x2;
//    node.syscall_number = __NR_write;
//    sprintf(pa, " %d" , a);
//    sprintf(pc, " %d" , c);
//    strcpy(pb,b);
//    res = agent_syscall(node);
//    res = get_res(res);
//    return res;
//}
//
//
//
////重新定义read库函数的包装
//int read(int a, char* b, int c){
//
//
//}


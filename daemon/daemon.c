//
// daemon 主程序
//
#include "../headers/semaphore_helper.h"
#include "../headers/ring_buffer.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/lsca_syscall.h"
#include <time.h>
#define EXIT_CODE 777

//test server's syscall listen
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define ECHO_SIZE 32


char log_flag = 1;  //日志记录标志变量
char redirect_flag = 0; //重定向标志变量
char redirect_path[64];

Node* current_node = NULL;  //当前节点
RingBuffer* buf = NULL;
int (*syscall_agent_table[SYSCALL_AGENT_MAX])(); //系统调用表，实质是函数指针数组


/**
 * 可选的记录日志
 * @param n
 */
void lsca_log(Node* n){
    //TODO:当前只做演示，完善时接入数据库
    //printf("lsca_daemon is processing a syscall\n");
    //printf("syscall_number is %d\n",n->syscall_number);
    //printf("x1 is :  %s\n",n->x1);
    FILE *fp = NULL;
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    fp = fopen("./log.txt", "a");
    fprintf(fp, "Time   : %d.%d.%d %d:%d:%d\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
    fprintf(fp, "SysNum : %d\n",n->syscall_number);
    fprintf(fp, "Param  :  %s  %s  %s\n\n",n->x0,n->x1,n->x2);
    fclose(fp);
}


/**
 * daemon退出程序
 * @return
 */
int daemon_exit(){

    while (delete_shm(buf));
    printf("%s :  LSCA daemon is exiting!\n", __func__);
    return 0;

}

/**
 * 执行系统调用代理任务
 * @param task 当前要执行的任务，任务取自ring_buffer 的 queue 中的最靠前的 node
 * @return
 */
int exec_task(Node* task){
    //TODO:通过系统调用代理表执行任务，传递参数，考虑到参数数量和类型不定直接传递节点
    return syscall_agent_table[task->syscall_number](task);
}

/**
 * 持续监听是否有任务需要完成，接收到结束信号则返回
 * @return
 */
int listen_tasks(){
    //循环判断是否有任务需要完成
    for(; ;)
    {
        if(!lock_shm()){
            if(is_buffer_empty(buf)){
                unlock_shm();
                usleep(10000);
                continue;
            }
            current_node = queue_front(buf);
            if(current_node == NULL){
                printf("current_node is NULL\n");
            }
            if(log_flag == 1){
                lsca_log(current_node);
            }
            //TODO: 处理任务，后续多线程改进:
            int res;
            res = exec_task(current_node);
            if(res == -1){
                printf("lsca_daemon :  execute task failed! syscall_num : %d\n",current_node->syscall_number);
            }
            //del_task(buf);
            //传递结果缓冲区
            return_value_to_user(buf,current_node->res_buf_number,res);
            //返回结果后就可以清空传递参数所用的内存了
            memset(current_node,0,sizeof(current_node));
            //TODO:优化减少lock_time
            unlock_shm();
        }else{
            //TODO: 休眠
            usleep(100000);
        }

        //TODO: daemon退出，后续需优化成接收信号的方式
        if(current_node->syscall_number == EXIT_CODE){
            if(daemon_exit() == -1){
                printf("daemon_exit failed!");
                break;
            } else{
                return 0;
            }
        }
        usleep(1000);
    }
    return 0;
}

/**
 * 初始化系统调用代理表，当添加新的应用时在此处加入一条，格式为：syscall_agent_table[__NR_xxx] = agent_xxx
 * @return 成功返回0
 */
int init_syscall_agent_table(){
    syscall_agent_table[__NR_read] = agent_read;
    syscall_agent_table[__NR_write] = agent_write;
    syscall_agent_table[__NR_stop_daemon] = daemon_exit;
    syscall_agent_table[__NR_socket] = agent_socket;
    syscall_agent_table[__NR_bind] = agent_bind;
    syscall_agent_table[__NR_listen] = agent_listen;
    syscall_agent_table[__NR_accept] = agent_accept;
    syscall_agent_table[__NR_connect] = agent_connect;
    return 0;
}

/**
 * 初始化daemon
 * @param num队列节点数量
 * @return 大于零则初始化成功，否则初始化失败。
 */
int init_daemon(int num_of_nodes) {
    printf("%s :  LSCA daemon is starting up\n", __func__ );
    printf("%s :  start initial ring buffer\n", __func__ );
    buf = init_buffer(num_of_nodes);
    if(buf == NULL){
        printf("%s :  init buffer failed!\n", __func__ );
        return -1;
    }
    printf("%s :  start initial syscall_agent_table\n", __func__ );
    if(init_syscall_agent_table()){
        printf("%s :  init syscall_agent_table failed\n", __func__ );
    }
    printf("%s :  start providing services to user programs\n", __func__ );
    if(listen_tasks() == -1){
        printf("%s :  stop listening due to error!\n", __func__ );
    }
}

int listen_test()
{
    int listenfd, connfd;    //监听描述符，连接描述符
    struct sockaddr_in server_addr, client_addr;//16 bytes
    /*socket函数*/
    listenfd=socket(AF_INET, SOCK_STREAM, 0);
    /*服务器地址*/
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(12345);
    /*bind函数*/
    if(bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        perror("bind error");
    /*listen函数*/
    if(listen(listenfd, 10) < 0)
        perror("listen error");
//    while(1)
//    {
//        if((connfd=accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0)
//            return 0;
//        close(listenfd);    //关闭监听描述符
//        printf("echo ok\n");
//        close(connfd);   //父进程关闭连接描述符
//    }
    return 0;
}




/**
 * lsca daemon 起点
 * @return
 */
int main(int argc, char **argv){
    //test for syscall_listen
    //listen_test();

    //检查输入参数,判断是否开启log
    if(argc<2){
        printf("usage1:daemon log\nusage2:daemon nlog\n");
        return 0;
    }
    //根据参数改变log_falg
    if(!strcmp(argv[1],"log")){
        log_flag = 1;
    }else if(!strcmp(argv[0],"nlog")){
        log_flag = 0;
    }else{
        perror("usage1:daemon log\nusage2:daemon nlog");
    }
    //根据参数改变redirect_flag
    if(argc >= 3){
        if(strcmp(argv[2],"redirect")){
            redirect_flag = 1;
        }
    }
    //初始化daemon
    if (init_daemon(RING_BUFFER_SIZE) == -1) {
        printf("%s :  !\n", __func__);
        printf("%s :  start up LSCA daemon failed!\n", __func__);
        return -1;
    } else {
        printf("%s :  LSCA daemon is exiting!\n", __func__);
        return 0;
    }
}

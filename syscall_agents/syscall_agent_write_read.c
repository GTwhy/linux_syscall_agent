#include "../headers/syscall_agent_write_read.h"
#include "../headers/daemon.h"
#include "../headers/ring_buffer.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
extern char redirect_flag;
extern char redirect_path[64];

/**
 *
 * @param task
 * @return
 */
int agent_write(Node* task){
    int res;
    //可选添加输出重定向，定向到来源tty或pts
    if(redirect_flag == 1){
        int black_hole;//获得write调用返回值又不污染界面，导入到/dev/null
        char str[sizeof(atoi(task->x1))+strlen("echo ")+strlen(redirect_path)];
        strcpy(str,"echo ");
        strcat(str,task->x1);
        strcat(str,redirect_path);
        printf("%s\n",str);
        system(str);
        //获得write返回值，输出到null
        black_hole = open("/dev/null",O_WRONLY);
        res = write(black_hole,task->x1,atoi(task->x2));
        close(black_hole);
    } else{
        res = write(atoi(task->x0),task->x1,atoi(task->x2));
    }
    return res;
}

int agent_read(Node* task){
    int res;
    char res_buf[64];

    /*重定向测试*/
//    if(atoi(task->x0) == 0){
//        FILE *stream;
//        memset(res_buf, '\0', sizeof(res_buf) );//初始化buf,以免后面写如乱码到文件中
//        stream = popen( "cat << '\\0'", "w" ); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
//        fread(res_buf, sizeof(char), sizeof(res_buf), stream); //将刚刚FILE* stream的数据流读取到buf中
//        printf("%s\n",res_buf);
//        pclose(stream);
//    }
//    char buf[32]

    //fgets_test
//    if(atoi(task->x0) == 0){
//        FILE *fp;
//        fp = fopen("/dev/pts/3","r");
//        fgets(res_buf,32,fp);
//        printf("%s\n",res_buf);
//        fclose(fp);
//    }
    memset(res_buf,0,sizeof(res_buf));
    res = read(atoi(task->x0),res_buf,atoi(task->x2));
    memset(task->stack,0,sizeof(task->stack));
    return_buffer_to_user(task,res_buf);
    return res;
}
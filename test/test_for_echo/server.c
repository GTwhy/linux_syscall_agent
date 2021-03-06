#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

//str_echo函数从套接字上回射数据
void str_echo(int sockfd)
{
    ssize_t n;
    char buf[1000];
    
again:
    while((n=read(sockfd, buf, 1000)) > 0)
    {
        write(sockfd, buf, n);
    }
    if(n<0 && errno==EINTR)
        goto again;
    else if(n<0)	
        return 0;   
}

int main(int argc, char **argv)
{   
    int listenfd, connfd;    //监听描述符，连接描述符
    pid_t childpid;    //子进程pid
    socklen_t clilen;    //客户IP地址长度
    struct sockaddr_in server_addr, client_addr;
    
    /*socket函数*/
    listenfd=socket(AF_INET, SOCK_STREAM, 0);

    /*服务器地址*/
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(12345);

    /*bindt函数*/
    if(bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        perror("bind error");    
    
    /*listent函数*/
    if(listen(listenfd, 10) < 0)
        perror("listen error");
    
    while(1)
    {

        if((connfd=accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0)
           return 0;
        close(listenfd);    //关闭监听描述符
        str_echo(connfd);    //处理请求
        close(connfd);   //父进程关闭连接描述符 
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{
    if(argc<2)    //检查输入参数
        perror("usage:echo_client <server addr>");
    
    int sockfd;    //网络套接字
    struct sockaddr_in server_addr;    //服务器地址
    printf("size of sockaddr : %ld",sizeof(server_addr));

    /*socket函数*/
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    
    /*配置服务器地址*/
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(12345);
    if((inet_pton(AF_INET, argv[1], &server_addr.sin_addr)) < 0)
        perror("invaild IP address");
    
    /*connect函数*/
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        perror("can't connect to server");
    
    /*ECHO处理函数*/
    char send[32],recv[32];
    
    /*从标准输入读取文本*/
    while(fgets(send, 32, stdin)!=NULL)
    {
        /*发送文本到服务器*/
        write(sockfd, send, strlen(send));
        
        /*接收从服务器返回*/
        if(read(sockfd, recv, 32)==0)
            perror("server terminated");
        
        /*打印到标准输出*/
        fputs(recv, stdout);
    }    
    return 0;
}

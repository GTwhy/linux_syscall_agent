//
// Created by why on 2020/8/13.
//
#include <stdint.h>
#include<time.h>
#include <stdio.h>

/* Internet address. */
struct in_addr {
    uint32_t       s_addr;     /* address in network byte order */
};

struct sockaddr_in {
    uint16_t   sin_family; /* address family: AF_INET */
    uint16_t     sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
    char    sin_zero[8];
};

struct sockaddr {
    uint16_t sin_family;//地址族
    char sa_data[14]; //14字节，包含套接字中的目标地址和端口信息
};


int main() {
    printf("socketaddr_in  %d\nsockaddr  %d\nin_addr  %d\n",sizeof(struct sockaddr_in),sizeof(struct sockaddr),sizeof(struct in_addr));
}
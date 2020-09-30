#ifndef LSCA_SYSCALL_WRAPPER_SOCKET_H
#define LSCA_SYSCALL_WRAPPER_SOCKET_H
#include <stdint.h>
#include <sys/types.h>
typedef unsigned int sa_family_t;
typedef unsigned int in_port_t;

///* Internet address. */
//struct in_addr {
//    uint32_t       s_addr;     /* address in network byte order */
//};
//
//struct sockaddr_in {
//    sa_family_t    sin_family; /* address family: AF_INET */
//    in_port_t      sin_port;   /* port in network byte order */
//    struct in_addr sin_addr;   /* internet address */
//};
//
//struct sockaddr {
//    sa_family_t sin_family;//地址族
//    char sa_data[14]; //14字节，包含套接字中的目标地址和端口信息
//};


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



int socket(int a, int b, int c);
int bind(int a, struct sockaddr *b, int c);
int listen(int a, int b);
int accept(int a,void *b, int *c);
int connect(int a, struct sockaddr *b, int c);



#endif //LSCA_SYSCALL_WRAPPER_SOCKET_H

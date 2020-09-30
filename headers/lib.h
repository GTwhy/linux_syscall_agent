#ifndef LSCA_LIB_H
#define LSCA_LIB_H

//参照Linux系统调用号
//#define __NR_read 63
//#define __NR_write 64
//#define __NR_socket 198
//#define __NR_socketpair 199
//#define __NR_bind 200
//#define __NR_listen 201
//#define __NR_accept 202
//#define __NR_connect 203
//#define __NR_getsockname 204
//#define __NR_getpeername 205
//#define __NR_sendmsg 211
//#define __NR_recvmsg 212

#include "ring_buffer.h"
#include <sys/types.h>


int agent_syscall(Node node);
int get_res(int res_num);
int get_res_with_buffer(int res_num, char *buf_ptr);
//int write(int a, char* b, int c);
//int read(int a, char* b, int c);
//int socket(int a, int b, int c);
//int bind(int a, struct sockaddr *b, int c);
//int listen(int a, int b);
//int accept(int a,void *b, int *c);

#endif //LSCA_LIB_H

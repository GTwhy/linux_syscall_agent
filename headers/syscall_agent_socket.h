
#ifndef LSCA_SYSCALL_AGENT_SOCKET_H
#define LSCA_SYSCALL_AGENT_SOCKET_H
#include "ring_buffer.h"
#include <sys/types.h>


int agent_socket(Node* task);
int agent_bind(Node* task);
int agent_listen(Node* task);
int agent_accept(Node* task);
int agent_connect(Node* task);


#endif //LSCA_SYSCALL_AGENT_SOCKET_H

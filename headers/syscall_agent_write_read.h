#ifndef LSCA_SYSCALL_AGENT_WRITE_READ_H
#define LSCA_SYSCALL_AGENT_WRITE_READ_H

#include "ring_buffer.h"
#include <sys/types.h>

int agent_write(Node* task);
int agent_read(Node* task);


#endif //LSCA_SYSCALL_AGENT_WRITE_READ_H

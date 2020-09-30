#ifndef LSCA_LSCA_SYSCALL_H
#define LSCA_LSCA_SYSCALL_H

#include "syscall_agent_write_read.h"
#include "syscall_agent_socket.h"
#include "syscall_agent_daemon_control.h"
#include <sys/types.h>

#define __NR_read 63
#define __NR_write 64
#define __NR_socket 198
#define __NR_bind 200
#define __NR_listen 201
#define __NR_accept 202
#define __NR_connect 203
#define __NR_stop_daemon 777

#endif //LSCA_LSCA_SYSCALL_H

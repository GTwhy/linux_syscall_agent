#ifndef LSCA_SYSCALL_WRAPPER_WRITE_READ_H
#define LSCA_SYSCALL_WRAPPER_WRITE_READ_H
#include <sys/types.h>
ssize_t write(int fd, void *buf, size_t  count);
ssize_t read(int fd, void *buf, size_t  count);
#endif //LSCA_SYSCALL_WRAPPER_WRITE_READ_H

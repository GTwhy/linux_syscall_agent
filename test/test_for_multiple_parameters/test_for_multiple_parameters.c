//
// Created by why on 2020/8/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
int print(const char *arg, ...)
{
    va_list args;
    const char *arg1;
    int arg2;
    va_start(args, arg);
    arg1 = va_arg(args, const char *);
    arg2 = va_arg(args, int );
    va_end(args);
    printf("arg=%s arg1=%s arg2=%d", arg, arg1, arg2);
}
int main()
{
    print("11111", "23333",123);
}
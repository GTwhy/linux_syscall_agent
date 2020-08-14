#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
struct Node{

    char x[128];
};

int test(){
    return 0;
}

int main() {
    struct Node node;
    void *n = node.x;
    void *s = "hello";
    memset(n,0,128);
    memcpy(n,s,strlen(s));
    printf("%s\n",n);
    s = "123";
    memcpy(n,s,strlen(s));
    printf("%d\n",atoi(n)+2);
    if(test()){
        printf("haha");
    }
    return 0;
}

#include <unistd.h>
void main(){
    for (int i = 0; i < 100; ++i) {
        write(1,"Hello World!\n",14);
    }
}
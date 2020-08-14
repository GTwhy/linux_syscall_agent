//
// Created by why on 2020/8/10.
//

#include <stdio.h>

int func1(){
    printf("func1\n");
    return 0;
}
int func2(int a){
    printf("func2 : %d\n", a);
    return 0;
}
int func3(int a, int b){
    printf("func3, : %d, %d\n", a, b);
    return 0;
}
char* func4(int a){
    printf("func4 : %d\n",a);
    return "aaa";
}

/**
 * 无论在声明函数指针数组时声明的返回值是什么，都可以存入各种返回值的函数只不过编译时会有警告，参数也可以任意设置
 * 使用返回值时无论是否强制类型转换都可以，猜测是因为一旦使用了单位符那么系统就将后续参数指向的内存认作相应类型的参数了
 * @return
 */
int main(){
    int (*func_pointer[4])();
    func_pointer[0] = func1;
    func_pointer[1] = func2;
    func_pointer[2] = func3;
    func_pointer[3] = func4;
    func_pointer[0]();
    func_pointer[1](1);
    func_pointer[2](1,2);
    printf("func4 return %s", (char*)func_pointer[3](1));
    return 0;
}
#include <stdio.h>
void func(int a,int b,int c,int d,char *s);
void func(int a,int b,int c,int d,char *s){
	
	printf("%x,%x,%x,%x\n",a,b,c,d);
	printf("%s\n",s);
}

int main()
{
	char *s = "hello";
	func(1,2,3,4,s);
	return 0;
}



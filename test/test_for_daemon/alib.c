#include<stdio.h>

int write(int a, char* b, int c){
	printf("xixi");
	printf(b);
	return 0;
	
}


int puts(char* s){
	write(1,"putsss",6);
	write(1,s,4);
	return 0;
}

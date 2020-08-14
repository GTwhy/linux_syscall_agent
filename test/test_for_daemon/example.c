#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>


int main(void)
{
	pid_t pid;

	pid = fork();

	if( pid == -1 )
	{
		perror("fork");
		exit(1);
	}
	else if( pid == 0)
	{
		write(1,"ch",2);

		sleep(3);

		printf("--------------child going to die------------------\n");
	}
	else
	{
		while(1)
		{
			write(1,"fa",2);
			sleep(1);	
		}
	}

	return 0;
} 

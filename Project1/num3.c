#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Incorrect syntax, use: %s <argument>\n", argv[0]);
		return 0;
	}
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		int i;
		i = system(argv[1]);
		printf("The Child PID: %d.\n", getpid());		
	}
	else
	{
		int status = 0;
		wait(&status);
		printf("Parent PID: %d. \n", getppid());
	}
	return 0;
}

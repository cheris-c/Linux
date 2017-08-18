/*************************************************************************
    > File Name: orphan.c
    > Author: Actually
    > Created Time: 2017年08月17日 星期四 15时22分35秒
 ************************************************************************/

#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int i = 10;

    pid = fork();
    switch(pid)
    {
    case 0:
	while(i)
	{
	    printf("A background process, PID:%d, ParentId: %d\n", getpid(), getppid());
	    sleep(3);
	    i--;
	}
	break;
    case -1:
	perror("Process creation failed\n");
	exit(-1);
    default:
	printf("I am parent process, my pid is %d\n", getpid());
	exit(0);
    }

    return 0;
}


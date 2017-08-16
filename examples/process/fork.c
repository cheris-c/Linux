/*************************************************************************
    > File Name: fork.c
    > Author: Actually
    > Created Time: 2017年08月16日 星期三 21时25分43秒
 ************************************************************************/

#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

int main()
{
    pid_t pid;
    char *msg;
    int k;

    printf("Process Creation Study\n");
    pid = fork();
    switch(pid)
    {
	case 0:
	    msg = "Child process is running";
	    k = 3;
	    break;
	case -1:
	    perror("Process creation failed\n");
	    break;
	default:
	    msg = "Parent process is running";
	    k = 5;
	    break;
    }

    while(k > 0)
    {
	puts(msg);
	sleep(1);
	k--;
    }

    return 0;
}



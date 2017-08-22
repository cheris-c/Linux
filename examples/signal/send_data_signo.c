/*************************************************************************
  > File Name: send_data_signo.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 11时17分59秒
 ************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//选项-d后跟待传递的数据，选项-s后跟待发送的信号，选项-p后跟目的进程的进程ID
int main(int argc,char *argv[])
{
    union sigval value;
    int signum = SIGTERM; //默认发送SIGTERM
    pid_t pid;
    int i;

    value.sival_int = 0;

    if (argc != 3 && argc != 5 && argc != 7)
    {
	printf("./send_data_signo <-d data> <-s signm> [-p][pid]\n");
	exit(1);
    }

    for (i = 1; i < argc; i++)
    {
	if (!strcmp(argv[i], "-d"))
	{
	    value.sival_int = atoi(argv[i+1]);
	    continue;
	}

	if (!strcmp(argv[i], "-s"))
	{
	    signum = atoi(argv[i+1]);
	    continue;
	}

	if (!strcmp(argv[i], "-p"))
	{
	    pid = atoi(argv[i+1]);
	    continue;
	}
    }

    if (sigqueue(pid, signum, value) < 0)
    {
	perror("sigqueue");
	exit(1);
    }

    return 0;
}

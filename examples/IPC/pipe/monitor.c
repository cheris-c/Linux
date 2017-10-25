/*************************************************************************
  > File Name: monitor.c
  > Description: use dup function redirect fd[0] to 0(stdin) 
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 19时17分14秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[], char **environ)
{
    int fd[2];
    pid_t pid;
    int stat_val;

    if (argc < 2)
    {
	printf("wrong parameters\n");
	exit(0);
    }

    if (pipe(fd))
    {
	perror("pipe failed\n");
	exit(1);
    }

    pid = fork();
    switch (pid)
    {
	case -1:
	    perror("fork failed\n");
	    exit(-1);
	case 0:
	    close(0);
	    dup(fd[0]);	//使用dup函数复制管道输入端fd[0]到标准输入，实现父子进程通信
	    execve("ctlprocess", (void *)argv, environ);
	    exit(0);
	default:
	    close(fd[0]);
	    sleep(3);
	    write(fd[1], argv[1], strlen(argv[1])+1);
	    break;
    }

    wait(&stat_val);
    exit(0);
}

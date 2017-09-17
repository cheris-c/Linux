/*************************************************************************
  > File Name: dual_pipe.c
  > Description: Realize full-duplex communication by two pipes
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 18时25分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void child_rw_pipe(int readfd, int writefd)
{
    char *msg1 = "from child process！\n";
    write(writefd, msg1, strlen(msg1)+1);

    char msg2[100];
    read(readfd, msg2, 100);
    printf("child process read from pipe:%s", msg2);
}

void parent_rw_pipe(int readfd, int writefd)
{
    char *msg1 = "from parent process\n";
    write(writefd, msg1, strlen(msg1)+1);

    char msg2[100];
    read(readfd, msg2, 100);
    printf("parent process read form pipe: %s\n", msg2);
}

/*
    在这种情况下子进程可以共享父进程的文件描述符，但是如果子进程调用exec函数执行另外一个程序时，
就不能再共享了。此时可以将子进程中的文件描述符重定向到标准输入, 当新执行的程序从标准输入获取数据
时实际上是从父进程中获取输入数据.dup和dup2函数提供了复制文件描述符的功能, 使用方法查看others.txt
*/
int main()
{
    pid_t pid;
    int stat_val;
    int fd1[2], fd2[2];

    printf("realize full-duplex communication\n");
    if (pipe(fd1) < 0)
    {
	printf("fd1 failed!\n");
	exit(1);
    }
    if (pipe(fd2) < 0)
    {
	printf("pipe2 failed!\n");
	exit(1);
    }

    pid = fork();
    switch(pid)
    {
	case -1:
	    printf("fork error\n");
	    exit(-1);
	case 0:
	    close(fd1[1]);
	    close(fd2[0]);
	    child_rw_pipe(fd1[0], fd2[1]);
	    exit(0);
	default:
	    close(fd1[0]);
	    close(fd2[1]);
	    parent_rw_pipe(fd2[0], fd1[1]);
	  
	    wait(&stat_val);
	    exit(0);
    }

    return 0;
}

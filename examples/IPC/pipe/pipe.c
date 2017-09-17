/*************************************************************************
  > File Name: pipe.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 15时56分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
    #include <unistd.h>
    int pipe(int fd[2]]);
    成功返回0，失败返回-1。
注意：
    管道两端的任务是固定的，一端称为读端，用fd[0]标识，另一端为写端，用fd[1]标识.
    管道是一种文件，因此对文件的I/O函数都可以用于管道，如read()、write()等。
    管道只能用于有亲缘关系的进程间通信，在各进程进行通信时，他们共享文件描述符。在
使用前应该及时的关闭管道另一端，以避免意外错误发生。
 */

void read_from_pipe(int fd)
{
    char message[100];
    read(fd, message, 100);
    printf("read from pipe : %s\n", message);
}

void write_to_pipe(int fd)
{
    char *message = "hello pipe\n";
    write(fd, message, strlen(message)+1);
}

int main()
{
    pid_t pid;
    int fd[2];
    int stat_val;
    
    //必须在fork之前调用pipe(),否则子进程不会继承管道文件描述符
    if (pipe(fd) < 0)
    {
	printf("create pipe failed\n");
	exit(1);
    }

    pid = fork();
    switch(pid)
    {
	case -1:
	    printf("fork error\n");
	    exit(0);
	case 0:
	    close(fd[1]);
	    read_from_pipe(fd[0]);
	    exit(0);
	default:
	    close(fd[0]);
	    write_to_pipe(fd[1]);
	    wait(&stat_val);
	    exit(0);
    }

    return 0;	
}

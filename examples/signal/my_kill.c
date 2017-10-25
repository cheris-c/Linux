/*************************************************************************
  > File Name: my_kill.c
  > Description: test function kill() and implent a simple command like kill 
  > Author: Actually
  > Created Time: 2017年08月21日 星期一 18时12分15秒
 ************************************************************************/

//不支持-l选项，只支持信号的编号而不是信号名发送信号
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/*
    kill(pid_t pid, int sig); //System Call
    pid  >  0: 则发送信号给进程号为pid的进程
    pid ==  0：发送信号给当前进程组里所有进程
    pid == -1：则把信号sig广播至系统内除1号进程和自身以外的所有进程；
    pid <  -1: 则发送信号sig给属于进程组-pid的所有进程

    当sig == 0时，则kill()函数仍执行正常的错误检查，但不发送信号，可以利用这一点
来确定mount进程是否有权向另外一个进程发送信号。如果向一个并不存在的进程发送空信号，
则kill()出错，kill函数出错返回-1，成功返回0.

注意：
    只有具有root权限的进程才能向其他任一进程发送信号，非root权限的进程只能向属于同
一个组或者同一个用户的进程发送信号。

其他类似函数:
int raise(int sig); 
    sends a signal to the calling process or thread. In a single-threaded program it 
is equivalent to 
	kill(getpid(), sig);
    In a multithreaded program it is equivalent to 
	pthread_kill(pthread_self(), sig);

    If the signal cause a handler to be called, raise() will return only after the 
signal handler has returned.

int sigqueue(pid_t pid, int sig, const union sigval value);
    用来发送信号sig给进程pid，与kill系统调用不用的是，sigqueue在发送信号的同时支持
信号携带参数；另一个不同点是sigqueue不能给一组进程发送信号。
    参数value是一个共用体：
	union{
	    int sigval_int;
	    void *sival_ptr;
	}	
    信号携带的参数要么是一个整型，要么是一个void型指针。当接收进程的信号处理函数是由
sigaction函数设置的并且设置了SA_SIGINFO标志（只有设置了SA_SIGINFO标志参数处理函数才
被设定为具有三参数的sa_sigaction）时，接收进程可以从结构体siginfo_t的si_value域取得
信号发送时携带的数据。
    函数执行成功返回0, 表明函数被成功发送到目标进程，当有错误发生时返回-1，错误代码存
入errno。

详细内容请查看 man 手册
 */

int main(int argc, char* argv[])
{
    int i, j;
    int signum = SIGTERM; //默认发送SIGTERM
    pid_t pid;

    if (argc != 2 && argc != 4)
    {
	printf("Usage: ./my_kill <-s signum> [PID]\n");
	exit(0);
    }

    for (i = 1; i < argc; i++)
    {
	if (0 == strcmp(argv[i], "-s"))
	{
	    signum = atoi(argv[i+1]);
	    break;
	}
    }

    if (argc == 2)
    {
	pid = atoi(argv[1]);
    }
    else
    {
	for (j = 1; j < argc; j++)
	{
	    if (j != i && j != i+1)
	    {
		pid = atoi(argv[j]);
		break;
	    }
	}
    }

    if (kill(pid, signum) < 0)
    {
	perror("kill");
	exit(1);
    }

    return 0;
}

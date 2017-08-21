/*************************************************************************
    > File Name: my_sigaction.c
    > Author: Actually
    > Created Time: 2017年08月21日 星期一 14时50分54秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int temp = 1;

void handler_sigint()
{
    printf("recv SIGINT\n");
    sleep(3);
    temp += 1;
    printf("the value of temp is : %d\n", temp);
    printf("in handler_sigint, after sleep\n");
}

int main()
{
    struct sigaction act;
    int i = 5;

    act.sa_handler = handler_sigint;
/*
    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    signum可以是SIGSTOP和SIGKILL以外的任何信号，如果act不为空，设置新的信号处理函数，如果oldact不是空指针，则旧的信号处理函数将被存储在oldact中。

       struct sigaction
       {
	    void (*sa_handler)(int);
	    void (*sa_sigaction)(int, siginfo_t *, void *);
	    sigset_t sa_mask;
	    int sa_flags;
	    void (*sa_restorer)(void);
       }
       sa_mask成员声明一个信号集，在调用信号捕捉函数之前，该信号集会增加到进程的信号屏蔽码中,
    新的信号屏蔽码会自动包括正在处理的信号(sa_flags未指定SA_NODEFER或SA_NOMASK),当信号从捕捉函数
    返回时，进程的信号屏蔽码会恢复原来的值。因此如果未设定sa_flags为SA_NODEFFER或SA_NOMASK，则当
    正在处理这个信号时，如果这种信号再次发生，那么它会阻塞到本次信号处理程序结束为止；若这种信号
    发生多次则对于不可靠信号（1-31），它只会被阻塞一次，即本次执行处理结束后只会再处理一次（相当
    于丢失了信号），对于可靠信号（33-64实时信号），则会被阻塞多次，即信号不会丢失，信号发生多少
    次，就会调用多少次信号处理函数。
	sa_flags 成员说明信号处理的一些其他相关操作
	    SA_NOCLDSTOP: 如果参数signum为SIGCHLD,则当子进程暂停时，并不会通知父进程。
	    SA_ONESHOOT或SA_RESETHAND: 在调用新的信号处理函数之前，将此信号的处理方式改为系统默认。
	    SA_ONSTACK：以预先定义好的堆栈调用信号处理函数
	    SA_RESTART: 被信号中断的系统调用，在信号处理函数执行完毕后会自动重新开始执行（BSD操作系统默认的方式）
	    SA_NOMASK或SA_NODEFFER: 在处理此信号结束前允许此信号再次递送，相当于中断嵌套
	    SA_SIGINFO: 如果设置了该标志，则处理函数由具有三个参数的sa_sigaction指定而不是sa_handler指定
    
其他详细内容查看 man 手册
 */

   // act.sa_flags = SA_NOMASK;      

    sigaction(SIGINT, &act, NULL);

    while (i--)
    {
	sleep(3);
	printf("while...\n");
    }

    return 0;
}

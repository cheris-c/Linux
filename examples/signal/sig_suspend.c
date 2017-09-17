/*************************************************************************
  > File Name: sig_suspend.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 09时50分04秒
 ************************************************************************/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
    #include <signal.h>
    int sigsuspend(const sigset_t *mask);
    sigsuspend函数将进程的信号屏蔽码设为mask，然后与pause函数一样等待信号的发生
并执行完信号处理函数。执行完后再把进程的信号屏蔽字设置为原来的屏蔽字，然后
sigsuspend函数才返回。它保证了改变进程的屏蔽码和将进程挂起等待信号是原子操作。
    sigsuspend函数总是返回-1，并将错误码置为EINTR。
    
    #include <unistd.h>
    int pause(void);
    pause() cause the calling process(or thread) to sleep() until a signal is delivered
that either terminates the process or causes the invocation（调用） of a signal-catching function.
    pause() returns only when a signal was caught and the signal-catching function returned. 
In this case pause() returns -1，and errno is set to EINTR.
 */

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line : %d", line);
    perror(err_string);
    exit(1);
}

void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
}

int main()
{
    sigset_t newmask, oldmask, zeromask;

    if (signal(SIGINT, handler_sigint) == SIG_ERR)
    {
	my_err("signal", __LINE__);
    }

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
	my_err("sigprocmask", __LINE__);
    }
    else
    {
	printf("SIGINT blocked\n");
    }

    printf("sleep 3 seconds\n");
    sleep(3);
    printf("after 3 seconds\n");

    //取消所有信号的屏蔽并等待信号的触发
    if (sigsuspend(&zeromask) != -1)  //总是返回-1
    {
	my_err("sigsuspend", __LINE__);
    }
    else
    {
	printf("recv a signo, return from sigsuspend\n");
    }

    //使用sigprocmask + pause可能会出错, 如果信号发生在sigprocmask之后pause之前则这个
    //信号会丢失掉，且如果信号只发生一次，程序永远挂起在pause上。 ???
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
	my_err("sigprocmask", __LINE__);
    }
    printf("sleep 5 seconds, test the error...\n");
    sleep(5);
    printf("after 5 seconds, pause start...\n");
    pause();

    //恢复信号屏蔽字
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
	my_err("sigprocmask", __LINE__);
    }

    while (1)
    {
	;
    }
    

    return 0;
}

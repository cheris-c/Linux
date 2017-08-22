/*************************************************************************
  > File Name: signal_mask.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 09时06分23秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/*
    #include <signal.h>
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
    int sigpending(sigset_t *set);
    (1)sigprocmask函数可以检测和更改进程的信号屏蔽码。如果参数oldset是非空指针，则该进程之前
的信号屏蔽码通过oldset返回；如果参数set是非空指针，则根据how的值来修改信号当前屏蔽码，how的
取值如下：
    SIG_BLOCK: 将进程新的信号屏蔽码设置为当前信号屏蔽码和set指向信号集的并集
    SIG_UNBLOCK: 将进程新的信号屏蔽码设置为当前信号屏蔽码中删除set所指向的信号集，即set包含
的是我们希望解除阻塞的信号，即使对当前信号屏蔽码中不存在的信号使用SIG_UNBLOCK也是合法操作。
    SIG_SETMASK: 将进程新的信号屏蔽码设置为set所指向的值。
    函数执行成功返回0， 当所有错误发生时则返回-1， 错误代码存入errno。
   （2）sigpending用来获取调用进程因被阻塞而不能递送和当前未决的信号集，该信号集通过set返回
函数执行成功返回0，有错误返回-1，错误代码存入errno中。
*/

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line: %d ", line);
    perror(err_string);
    exit(1);
}

void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
}

int main()
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGINT, handler_sigint) == SIG_ERR)
	my_err("signal", __LINE__);

    sleep(10);

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
	my_err("sigprocmask", __LINE__);
    }
    else
    {
	printf("SIGINT blocked\n");
    }

    sleep(10);

    if (sigpending(&pendmask) < 0)
    {
	my_err("sigpending", __LINE__);
    }
    switch (sigismember(&pendmask, SIGINT))
    {
	case 0:
	    printf("SIGINT is not in pending queue\n");
	    break;
	case 1:
	    printf("SIGINT is in pending queue\n");
	    break;
	case -1:
	    my_err("sigismember", __LINE__);
	    break;
	default:
	    break;
    }

    //分析程序结果可知，当我们在解除SIGINT信号阻塞之前，如果多次发送SIGINT信号，在
    //调用sigprocmask解除对SIGINT信号的阻塞以后，进程未决信号队列非空，首先执行信号
    //处理函数，因此我们可以看到打印了一次recv SIGINT，由此我们也看出SIGINT是不可靠
    //信号，不支持排队，有可能丢失。
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
	my_err("sigprocmask", __LINE__);
    }
    else
    {
	printf("SIGINT unblocked\n");
    }

    while (1)
    {
	;
    }
    

    return 0;
}

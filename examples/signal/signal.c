#include <stdio.h>
#include <signal.h>


void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
}

/*
   Linux中没有16和32号信号，其中1~31号信号是不可靠信号，33~64号信号是可靠信号，也称为实时信号。
信号的可靠性指的是信号是否会丢失或者说信号是否支持排队。
   SIGSTOP和SIGKILL这两个信号不能被忽略也不能被捕获和阻塞。

    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighanler_t handler);
    signum可以是SIGSTOP和SIGKILL外的任何信号，handler如果不是指针的话，则必须是SIG_IGN和SIG_DFL中
的一个。
    signal函数执行成功返回以前的信号处理函数指针，失败返回SIG_ERR（-1）。
 */

int main()
{
    int i = 5;
    signal(SIGINT, handler_sigint);
    while (i--)
    {
        printf("hello\n");
        sleep(2);
    }

    return 0;
}

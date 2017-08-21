/*************************************************************************
    > File Name: wrong_return.c
    > Description: test fuction setjmp(jmp_buf env) and longjmp(jmp_buf env, int val)
    > Author: Actually
    > Created Time: 2017年08月21日 星期一 15时53分36秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

jmp_buf env;  //保存待跳转位置的栈信息

//信号SIGRTMIN+15的处理函数
void handler_sigrtmin15(int signo)
{
    printf("recv SIGRTMIN+15\n");
    longjmp(env, 1); //返回到env处，注意第二个参数的值
}

//信号SIGRTMAX-15的处理函数
void handler_sigrtmax15(int signo)
{
    printf("recv SIGRTMAX-15\n");
    longjmp(env, 2);  //返回env处，注意第二个参数
}

/*
    setjmp(jmp_buf env);    longjmp(jmp_buf env, int val);
    参数env是一个特殊类型jmp_buf变量，里面存放的是在调用longjmp时能用来恢复栈状态
的所有信息。一般来说，env是一个全局变量，因为需要从另外一个函数中引用它。我们可以
在希望返回的位置使用setjmp,直接调用setjmp时返回0；当从longjmp返回时，setjmp的返回
值是longjmp的第二个参数的值可以利用这一点是多个longjmp返回到一个setjmp处。

    观察输出结果，当我们多次发送信号时，信号处理时会自动阻塞正在被处理的信号，在信
号处理函数返回时把进程屏蔽字恢复，即解除对当前信号的阻塞。然而在本例中由于信号处理
函数通过longjmp函数直接跳转至setjmp处，信号处理函数没有正常返回，所以在进程信号屏蔽
字在第一次收到消息后，就把信号设为阻塞，并且再也没有恢复，因而再也触发不了信号处理
函数了，除非手动将进程对信号的屏蔽去除。
*/

int main()
{
    int i = 5;

    switch (setjmp(env))
    {
	case 0:
	    break;
	case 1:
	    printf("return from SIGRTMIN+15\n");
	    break;
	case 2:
	    printf("return from SIGRTMAX-15\n");
	    break;
	default:
	    break;
    }

    signal(SIGRTMIN+15, handler_sigrtmin15);
    signal(SIGRTMAX-15, handler_sigrtmax15);

    while (i--)
    {
	sleep(10);
	printf("while...\n");
    }

    return 0;
}

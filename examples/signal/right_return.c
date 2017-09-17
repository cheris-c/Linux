/*************************************************************************
  > File Name: right_return.c
  > Description: test funciton siglongjmp(sigjum_buf env, int savesigs) and sigsetjmp(sigjmp_buf env, int val)  
  > Author: Actually
  > Created Time: 2017年08月21日 星期一 17时43分34秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

#define ENV_UNSAVE 0
#define ENV_SAVED  1

int flag_saveenv = ENV_UNSAVE;
jmp_buf env;  

void handler_sigrtmin15(int signo)
{
    if (flag_saveenv == ENV_UNSAVE)
    {
	return;
    }
    printf("recv SIGRTMIN+15\n");
    sleep(5);
    printf("in handler_sigrtmin15, after sleep\n");
    siglongjmp(env, 1);
}

/*
    sigsetjmp(sigjmp_buf env, int savesigs);比setjmp(jmp_buf env)多了一个参数
savesigs，如果savesigs非零，则sigsetjmp在env中保存当前进程的当前屏蔽字，在调用
siglongjmp(sigjmp_buf env, ing val)时会从其中恢复保存的信号屏蔽字。

    观察输出结果可知，当我们发送四次SIGRTMIN+15信号，四次信号都被响应，可见实时
信号都是可靠的.
 */

int main()
{
    int i = 5;

    switch(sigsetjmp(env, 1))
    {
	case 0:
	    printf("first call sigsetjmp()\n");
	    flag_saveenv = ENV_SAVED;
	    break;
	case 1:
	    printf("return from SIGRTMIN+15\n");
	    break;
	default:
	    printf("error input");
	    break;
    }

    signal(SIGRTMIN+15, handler_sigrtmin15);
    while (i--)
    {
	printf("while...\n");
	sleep(10);
    }

    return 0;
}

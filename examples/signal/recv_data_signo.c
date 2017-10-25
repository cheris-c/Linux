/*************************************************************************
  > File Name: recv_data_signo.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 11时34分45秒
 ************************************************************************/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void handler_sigint(int signo, siginfo_t *siginfo, void *pvoid)
{
    printf("recv SIGINT, the data value is : %d\n", siginfo->si_int);
}

int main()
{
    struct sigaction act;
    
    act.sa_sigaction = handler_sigint;
    act.sa_flags = SA_SIGINFO; //使用三参数的信号处理函数
    
    sigaction(SIGINT, &act, NULL);

    while (1)
    {
	;
    }

    return 0;
}

/*************************************************************************
  > File Name: alarm.c
  > Description: Send a packet on time
  > Author: Actually
  > Created Time: 2017年08月21日 星期一 20时15分37秒
 ************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/*
    unsigned int alarm(unsigned int seconds); //System Call
    可以用来设置定时器，经过seconds秒后，内核将给调用该函数的进程发送SIGALARM信号。如果
seconds为0，则不再发送SIGALARM信号。最新一次调用alarm函数将取消前一次的设定.
    如果之前调用过alarm，则返回之前设定的定时器剩余时间；否则如果之前没有设置过定时器，
则返回0。

注意：
    alarm只设定为发送一次信号，要想用alarm多次发送，就要对alarm进行对此调用
 */

void send_ip()
{
    printf("send a icmp echo request packet\n");
}

void recv_ip()
{
    while(1)
    {
	;
    }
}

void handler_sigalarm(int signo)
{
    send_ip();
    alarm(2);
}

int main()
{
    signal(SIGALRM, handler_sigalarm);

    raise(SIGALRM);
    recv_ip();

    return 0;
}

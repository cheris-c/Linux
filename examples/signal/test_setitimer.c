/*************************************************************************
  > File Name: test_setitimer.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月21日 星期一 21时12分25秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

/*
    setitimer也是用来设置定时器的，而且和alarm使用同一个定时器，因此会相互影响。
   int getitimer(int which, struct itimerval *value);
   int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
	第一个参数用来指定使用哪个定时器,根据参数which可单独设定每个定时器,定时器的种类如下:
    ITIMER_REAL: 按实际时间计时，计时到达时将给进程发送SIGALRM信号，相当于高精度的alarm函数；
    ITIMER_VIRTUAL: 仅当进程执行时才开始计时。计时到达时将给进程发送SIGVTALRM信号；
    ITIMER_PROF: 进程执行的时间以及内核因本进程而消耗的时间都计时。与ITIMER_VIRTUAL搭配使用，
    通常用来统计进程在用户态和核心态花费的时间的总和。计时到到达时发送SIGPROF信号。
    struct itimerval
    {
	struct timerval it_interval; //next value
	struct timeval it_value;     //current value
    };
    struct timeval
    {
	time_t tv_sec;       //seconds
	suseconds_t tv_usec; //microseconds
    };
    
    对于函数getitimer，如果存在由which指定的定时器，则将剩余时间保存在it_value中，该定时器的
初始值保存在it_interval中，如果不存在指定类型的定时器，则将value置为0返回。执行成功返回0，有
错误发生返回-1，错误代码存入errno。
    对于函数setitimer，参数ovalue如果不是空指针，则将上次设定的定时器的值存入其中。定时器从
value递减为0时，产生一个信号，并将it_value的值设为it_interval,然后重新开始计时，周而复始.仅当
it_value的值为0或者计时到达而it_interval的值为0时，停止计时。执行成功返回0，有错误发生返回-1，
错误代码存入errno。
 */

void handler_sigtime(int signo)
{
    switch (signo)
    {
	case SIGALRM:
	    printf("recv SIGALRM  %d\n", signo);
	    break;
	case SIGPROF:
	    printf("recv SIGPROF  %d\n", signo);
	    break;
	default:
	    break;
    }
}

int main()
{
    struct itimerval value;
    
    signal(SIGALRM, handler_sigtime);
    signal(SIGPROF, handler_sigtime);

    value.it_value.tv_sec = 1;		//第一次1秒触发信号
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 5;	//第二次开始每五秒触发信号
    value.it_interval.tv_usec = 0;	

    setitimer(ITIMER_REAL, &value, NULL);
    setitimer(ITIMER_PROF, &value, NULL);

    while (1)
    {
	;
    }

    return 0;
}

/*************************************************************************
  > File Name: test_setitimer.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月21日 星期一 21时12分25秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

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
 */

int main()
{
    return 0;
}

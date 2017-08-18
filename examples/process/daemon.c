/*************************************************************************
    > File Name: daemon.c
    > Author: Actually
    > Created Time: 2017年08月18日 星期五 14时14分43秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <syslog.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>

int setdaemon()
{
    int pid, i;

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();
    if (pid > 0)
    {
	exit(0); //父进程推出，使子进程成为后台进程
    }
    else if (pid < 0)
    {
	return -1;
    }

    setsid(); //建立一个新的进程组，在这个新的进程组中，子进程成为这个进程组的首进程，以使该进程脱离所有终端。

    //再一次创建一个子进程，推出父进程，保证该进程不是进程组长，同时让该进程无法再打开一个新的终端
    pid = fork();
    if(pid > 0) 
    {
	exit(0);
    }
    else if (pid < 0)
    {
	return -1;
    }

    //关闭所有从父进程继承的不需要的文件描述符
    for(i = 0; i < NOFILE; close(i++));

    //改变工作目录，使得进程不与任何文件系统联系
    chdir("/");
    
    //将文件屏蔽字设为0
    umask(0);
    signal(SIGCHLD, SIG_IGN);

    return 0;
}

int main()
{
    time_t now;
    setdaemon();
    syslog(LOG_USER|LOG_INFO, "测试守护进程\n");
    while(1)
    {
	sleep(8);
	time(&now);
	syslog(LOG_USER|LOG_INFO, "系统时间：\t%s\t\t\n", ctime(&now));
    }
}

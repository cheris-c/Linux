/*************************************************************************
    > File Name: mynice.c
    > Author: Actually
    > Created Time: 2017年08月18日 星期五 16时11分11秒
 ************************************************************************/

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int stat_val = 0;
    int oldpri, newpri;

    printf("nice study\n");
    pid = fork();
    switch(pid)
    {
	case 0:
	    printf("Child is running, CurPid is %d, ParentPid is %d\n", getpid(), getppid());
	    
	    oldpri = getpriority(PRIO_PROCESS, getpid());
	    printf("Old priority = %d\n", oldpri);

	    newpri = nice(2);
	    printf("new priority = %d\n", newpri);
	    exit(0);
	case -1:
	    perror("Process creation failed!\n");
	    break;
	default:
	    printf("Parent is running, ChildPid = %d, Pid = %d\n", pid, getpid());
	    break;
    }

    wait(&stat_val);
    return 0;
}

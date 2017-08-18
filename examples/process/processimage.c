/*************************************************************************
    > File Name: processimage.c
    > Author: Actually
    > Created Time: 2017年08月18日 星期五 15时45分31秒
 ************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char **envp)
{
    int i;

    printf("I am a process image!\n");
    printf("My pid = %d, parentpid = %d\n", getpid(), getppid());
    printf("uid = %d, gid = %d\n", getuid(), getgid());

    for (i = 0; i < argc; ++i)
	printf("argv[%d] = %s\n", i, argv[i]);

    return 0;
}

/*************************************************************************
  > File Name: ctlprocess.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月22日 星期二 19时29分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int n;
    char buf[1024];

    while(1)
    {
	if ((n = read(0, buf, 1024)) > 0)
	{
	    printf("%s\n", buf);
	    buf[n+1] = '\0';
	    printf("ctrlprocess receive: %s\n", buf);

	    if (strcmp(buf, "exit") == 0)
	    {
		exit(0);
	    }

	    if (strcmp(buf, "getpid") == 0)
	    {
		printf("My pid : %d\n", getpid());
		sleep(3);
		exit(0);
	    }
	}
    }

    return 0;
}

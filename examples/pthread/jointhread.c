/*************************************************************************
  > File Name: jointhread.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年09月13日 星期三 09时27分27秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>

void assist_thread(void *arg)
{
    printf("I am helping to do some jobs\n");
    sleep(3);
    pthread_exit(0);
}

int main()
{
    pthread_t thid;
    int status;

    pthread_create(&thid, NULL, (void *)assist_thread, NULL);
    pthread_join(thid, (void *)&status);

    printf("assistthread is exit is caused %d\n", status);

    return 0;
}

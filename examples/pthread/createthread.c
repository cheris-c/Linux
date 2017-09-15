/*************************************************************************
  > File Name: createthread.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年09月10日 星期日 08时58分13秒
 ************************************************************************/

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * #include <pthread.h>
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void* (*start_routine)(void *), void *arg);
 * 
 */

int* thread(void *arg)
{
    pthread_t newthid;

    newthid = pthread_self();
    printf("this is a new thread, threadID = %u\n", newthid);
    return NULL;
}

int main()
{
    pthread_t thid;

    printf("main thread, ID is %u\n");
    if (pthread_create(&thid, NULL, (void *)thread, NULL) != 0)
    {
        printf("thread creation failed\n");
        exit(1);
    }

    sleep(1);
    return 0;
}

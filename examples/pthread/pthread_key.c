/*************************************************************************
  > File Name: pthread_key.c
  > Description: create and use thread-specific data 
  > Author: Actually
  > Created Time: 2017年09月18日 星期一 12时01分33秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

pthread_key_t key;

void* thread_func2(void *arg)
{
    int tsd = 5;
    
    printf("thread %d is running...\n", pthread_self());
    pthread_setspecific(key, (void *)tsd);
    printf("thread %d is returns %d...\n", pthread_self(), pthread_getspecific(key));
}

void* thread_func1(void *arg)
{
    int tsd = 0;
    pthread_t thid2;

    printf("thread %d is running...\n", pthread_self());
    pthread_setspecific(key, (void *)tsd);
    pthread_create(&thid2, NULL, thread_func2, NULL);
    sleep(3);

    printf("thread %d is returns %d...\n", pthread_self(), pthread_getspecific(key));
}


int main()
{
    pthread_t thid;

    printf("main thread begins running...\n");
    pthread_key_create(&key, NULL);
    pthread_create(&thid, NULL, thread_func1, NULL);
    sleep(5);

    pthread_key_delete(key);
    printf("main thread exit...\n");

    return 0;
}



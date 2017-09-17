/************************************************************************************************
  > File Name: oncerun.c
  > Description: 在某些情况下，函数执行次数要被限制为一次，此时就需要使用pthread_once函数。
  > Author: Actually
  > Created Time: 2017年09月11日 星期一 12时46分32秒
 *************************************************************************************************/

/*该实例创建两个线程，两个线程通过pthread_once调用同一个函数，结果被调用的函数只被执行了一次*/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
    printf("Function run is running in thread %u\n", pthread_self());
}

void* thread1(void *arg)
{
    pthread_t thid = pthread_self();
    printf("Current thread's ID is %u\n", thid);
    pthread_once(&once, run);
    printf("thread1 ends\n");
}

void* thread2(void *arg)
{
    pthread_t thid = pthread_self();
    printf("Current thread's ID is %u\n", thid);
    pthread_once(&once, run);
    printf("thread2 ends\n");
}

int main()
{
    pthread_t thid1, thid2;

    //run函数只会在thread1中执行一次
    pthread_create(&thid1, NULL, thread1, NULL);
    pthread_create(&thid2, NULL, thread2, NULL);

    sleep(3);
    printf("main thread will exit...\n");

    return 0;
}



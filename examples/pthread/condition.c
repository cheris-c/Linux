/*************************************************************************
  > File Name: condition.c
  > Description: Thread synchronization
  > Author: Actually
  > Created Time: 2017年09月13日 星期三 20时26分36秒
 ************************************************************************/

//启动两个线程，并等待同一个条件变量。
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t  cond;

void* fst_thread(void *arg)
{
    pthread_cleanup_push(pthread_mutex_unlock, &mutex);

    while(1)
    {
        printf("thread1 is running...\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
     
        printf("thread1 applied the condition...\n");
        pthread_mutex_unlock(&mutex);

        sleep(3);
    }

    pthread_cleanup_pop(0);
}

void* scd_thread(void *arg)
{
    while(1)
    {
        printf("thread2 is running...\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        printf("thread2 applied the condition...\n");
        sleep(3);
    }
}

int main()
{
    pthread_t thid1, thid2;

    printf("condition variable study...\n");
    
    //初始化互斥锁和条件变量
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    //创建两个线程
    pthread_create(&thid1, NULL, (void *)fst_thread, NULL);
    pthread_create(&thid2, NULL, (void *)scd_thread, NULL);

    do 
    {
        pthread_cond_signal(&cond);
    } while(1);

    sleep(5);
    pthread_exit(0);
}

/*************************************************************************
  > File Name: server.c
  > Description: 演示信号量如何控制对资源的访问 
  > Author: Actually
  > Created Time: 2017年09月05日 星期二 21时31分08秒
 ************************************************************************/

#include <stdio.h>
#include <linux/sem.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

/*
 *     ser创建一个信号集，并对信号量循环减一，相当于分配资源;
 *     cli执行时检查信号量，如果其值大于0代表有资源可用，继续执行，如果小于等于
 * 0代表资源已经分配完毕，进程client退出。
 */

#define MAX_RESOURCE 5

int main()
{
    key_t         key;
    int           semid;
    union semun   semopts;
    struct sembuf sbuf = {0, -1, 0};

    if ((key = ftok(".", 's')) == -1)
    {
        perror("ftok error!\n");
        exit(1);
    }

    if ((semid = semget(key, 1, IPC_CREAT | 0666)) == -1)
    {
        perror("semget error!\n");
        exit(1);
    }

    semopts.val = MAX_RESOURCE;
    if (semctl(semid, 0, SETVAL, semopts) == -1)
    {
        perror("semctl error!\n");
        exit(1);
    }

    sleep(5);
    printf("sem_p begin...\n");
    while (1)
    {
        if (semop(semid, &sbuf, 1) == -1)
        {
            perror("semop error!\n");
            exit(1);
        }
        printf("semval--\n");
        sleep(3);
    }
    printf("sem_p end...\n");

    exit(0);
}


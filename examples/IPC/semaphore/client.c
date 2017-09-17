/*************************************************************************
  > File Name: client.c
  > Description: 演示信号量如何控制对资源的访问 
  > Author: Actually
  > Created Time: 2017年09月05日 星期二 21时30分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <linux/sem.h>
#include <sys/types.h>
#include <unistd.h>

/*
 *     ser创建一个信号集，并对信号量循环减一，相当于分配资源;
 *     cli执行时检查信号量，如果其值大于0代表有资源可用，继续执行，如果小于等于
 * 0代表资源已经分配完毕，进程client退出。
 */

int main()
{
    key_t       key;
    int         semid, semval;
    union semun semopts;

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

    while (1)
    {
        if ((semval = semctl(semid, 0, GETVAL, 0)) == -1)
        {
            perror("semctl error!\n");
            exit(1);
        }

        if (semval > 0)
        {
            printf("Still %d resources can be used\n", semval);
        }
        else
        {
            printf("No more resources can be used!\n");
            break;
        }

        sleep(3);
    }

    exit(0);
}

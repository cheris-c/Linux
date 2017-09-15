/*************************************************************************
  > File Name: share_mem.h
  > Description: 
  > Author: Actually
  > Created Time: 2017年09月07日 星期四 15时26分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <linux/shm.h>
#include <errno.h>

#define SHM_SIZE 1024

int createsem(const char *pathname, int proj_id, int members, int init_val)
{
    key_t       key;
    int         index, semid;
    union semun semopts;

    if ((key = ftok(pathname, proj_id)) == -1)
    {
        perror("ftok error!\n");
        return -1;
    }

    if ((semid = semget(key, members, IPC_CREAT | 0666)) == -1)
    {
        perror("semget call failed!\n");
        return -1;
    }

    semopts.val = init_val;
    for (index = 0; index < members; index++)
    {
        semctl(semid, index, SETVAL, semopts);
    }

    return semid;
}

int opensem(const char *pathname, int proj_id)
{
    key_t key;
    int semid;

    if ((key = ftok(pathname, proj_id)) == -1)
    {
        perror("ftok error!\n");
        return -1;
    }

    if ((semid = semget(key, 0, IPC_CREAT | 0660)) == -1)
    {
        perror("semget call failed!\n");
        return -1;
    }

    return semid;
}

//P操作函数
int sem_p(int semid, int index)
{
    struct sembuf buf = {0, -1, IPC_NOWAIT};
    
    if (index < 0)
    {
        perror("index of array is illegal!\n");
        return -1;
    }

    buf.sem_num = index;
    if (semop(semid, &buf, 1) == -1)
    {
        perror("a wrong operation to semaphore occurred!\n");
        return -1;
    }

    return 0;
}

//V操作函数
int sem_v(int semid, int index)
{
    struct sembuf buf = {0, 1, IPC_NOWAIT};

    if (index < 0)
    {
        perror("index of array is illegal!\n");
        return -1;
    }

    buf.sem_num = index;
    if (semop(semid, &buf, 1) == -1)
    {
        perror("a wrong operation to semaphore occurred!\n");
        return -1;
    }

    return 0;
}

//删除信号集函数
int sem_delete(int semid)
{
    return semctl(semid, 0, IPC_RMID);
}

//等待信号量为1
int wait_sem(int semid, int index)
{
    while (semctl(semid, index, GETVAL, 0) == 0)
    {
        sleep(1);
    }

    return 1;
}

int createshm(const char *pathname, int proj_id, size_t size)
{
    key_t key;
    int   shmid;

    if ((key = ftok(pathname, proj_id)) == -1)
    {
        perror("ftok error!\n");
        return -1;
    }

    if ((shmid = shmget(key, size, IPC_CREAT|0666)) == -1)
    {
        perror("shmget call failed!\n");
        return -1;
    }

    return shmid;
}

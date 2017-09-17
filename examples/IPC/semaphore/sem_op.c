/*************************************************************************
  > File Name: semop.c
  > Description: 测试信号量的常用操作
  > Author: Actually
  > Created Time: 2017年09月05日 星期二 14时22分26秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <unistd.h>

/*
 * int semop(int semid, struct sembuf *sops, unsigned nsops);
 *      第一个参数表示信号集的标识符，第二个参数sops指向进行操作的结构体数组首地址；
 * 第三个参数nsops指出将要进行操作的信号的个数。
 *      函数调用成功返回0，失败返回-1。
 *      第二个参数sops指向的结构体数组中，每个sembuf结构体对应一个特定信号的操作。因
 * 此对信号进行操作必须熟悉该数据结构，该结构体定义在linux/sem.h中。
 *      struct sembuf
 *      {
 *              unsigned short sem_num;  //信号在信号集中的索引
 *              short          sem_op;   //操作类型
 *              short          sem_flg;  //操作标志
 *      };
 * sem_op取值：
 *      sem_op>0        信号加上sem_op的值，表示进程释放控制的资源
 *      sem_op=0        如果没有设置IPC_NOWAIT，则调用进程进入睡眠状态，直到信号值为
 *                      0；否则进程不会睡眠，直接返回EAGAIN。
 *      sem_op<0        信号加上sem_op的值，若没有设置IPC_NOWAIT，则调用进程阻塞，直到
 *                      资源可用；否则进程直接返回EAGAIN。
 * sem_flg取值：
 *      IPC_NOWAIT:
 *      SEM_UNDO:
 *
 * int semctl(int semid, int semnum, int cmd, ...)
 *     通过semctl控制函数可以删除信号集、对内核维护的信号集的数据结构semid_ds进行设置，获
 * 取信号集中信号值等。
 *     函数中第一个参数为信号集的标识符,第二个参数semnum标识一个特定的信号，第三个参数cmd
 * 指明控制操作的类型，最后的"..."说明函数参数是可选的，它依赖于第三个参数cmd，它通过共用
 * 体变量semnu选择要操作的参数。semun定义在linux/sem.h中。
 *      union semun
 *      {
 *              int val;               //Value for SETVAL
 *              struct semid_ds *buf;  //Buffer for IPC_STAT, IPC_SET
 *              unsigned short *array; //Array for GETALL, SETALL
 *              struct seminfo *_buf;  //Buffer for IPC_INFO
 *      };
 *
 *  cmd取值为：
 *      IPC_STAT: 通过semun结构体的buf参数返回当前的semid_ds结构体
 *                注意：必须先分配一个semid_ds结构，并把buf设置为指向这个结构体。
 *      IPC_SET: 对信号集的属性进行设置
 *      IPC_RMID: 把semid指定的信号集从系统中删除
 *      GETPID：返回最后一个执行semop操作的进程
 *      GETVAL：返回信号集中semnum指定的信号的值
 *      GETALL：返回信号集中所有的信号的值
 *      GETNCNT：返回正在等待资源的进程的数量
 *      GETZCNT：返回正在等待完全空闲资源的进程数量
 *      SETVAL：设置信号集中semnum指定的信号的值
 *      SETALL：设置信号集中所有信号的值
 *
 */
int createsem(const char *pathname, int proj_id, int members, int init_val)
{
    key_t semkey;
    int   index, sid;
    union semun semopts;

    if ((semkey = ftok(pathname, proj_id)) == -1)
    {
        perror("ftok error!\n");
        return -1;
    }

    if ((sid = semget(semkey, members, IPC_CREAT | 0666)) == -1)
    {
        perror("semget call failed\n");
        return -1;
    }

    printf("key : %d\n", semkey);
    printf("semid : %d\n", sid);
    semopts.val = init_val;
    for (index = 0; index < members; index++)
    {
        semctl(sid, index, SETVAL, semopts);
    }

    return sid;
}     
int sem_p(int semid, int index)
{
    struct sembuf buf = {0, -1, IPC_NOWAIT};

    if (index < 0)
    {
        perror("index of array cannot equals a minus value!\n");
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

int sem_v(int semid, int index)
{
    struct sembuf buf = {0, 1, IPC_NOWAIT};

    if (index < 0)
    {
        perror("index of array cannot equals a minus value!\n");
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

int semval_op(int semid, int index, int cmd)
{
    if (index < 0)
    {
        perror("index of array cannot equals a minus value!\n");
        return -1;
    }

    if (cmd == GETVAL || cmd == SETVAL)
    {
        return semctl(semid, index, cmd, 0);
    }

    printf("function cannot surport cmd: %d\n", cmd);
    return -1;
}

int main()
{
    int semid = createsem(".", 32, 2, 32);
    int val = semval_op(semid, 0, GETVAL);
    printf("P操作之前 semval : %d\n", val);
    sem_p(semid, 0);
    val = semval_op(semid, 0, GETVAL);
    printf("P操作之后 semval : %d\n", val);
    sem_v(semid, 0);
    val = semval_op(semid, 0, GETVAL);
    printf("V操作之后 semval : %d\n", val);

    return 0;
}


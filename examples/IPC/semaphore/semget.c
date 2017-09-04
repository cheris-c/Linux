/*************************************************************************
  > File Name: semget.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年09月04日 星期一 23时17分44秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <unistd.h>

/*
 * int semget(key_t key, int nsems, int semflg);
 *      第一个参数是由ftok()得到的键值；第二个参数nsems指明要创建的信号集包含的信号个数
 * ，如果只是打开信号集，把nsems设为0即可；第三个参数semflg为操作标志，可以去如下值：
 *      函数执行成功返回一个信号集的标识符，失败返回-1。
 *      IPC_CREAT: 调用semget()时，它会将此值与系统中其它信号集的key进行对比，如果存
 * 在相同的key，说明信号集已经存在，此时返回该信号集的标识符，否则新建一个信号集并返
 * 回其标识符。
 *      IPC_EXCL: 该宏须和IPC_CREAT一起使用，否则没有意义。当semflg取IPC_CREAT|IPC_EXCL
 * 时，表示如果发现信号集已经存在，则返回错误，错误码为EEXIST.
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

int main()
{
    createsem(".", 32, 2, 43);

    return 0;
}

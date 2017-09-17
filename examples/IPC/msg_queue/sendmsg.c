/*************************************************************************
  > File Name: sendmsg.c
  > Description: send data to message queue 
  > Author: Actually
  > Created Time: 2017年08月26日 星期六 17时39分22秒
 ************************************************************************/

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE  256
#define PROJ_ID   32
#define PATH_NAME "."

/*
 * #include <sys/types.h>
 * #include <sys/ipc.h>
 * #include <sys/msg.h>
 *
 * int msgget(key_t key, int msgflg);
 * 根据键值创建一个新的消息队列或者访问一个已存在的消息队列。
 * msgget的参数key可以为ftok函数的返回值。msgflg是一个标志参数：
 *      IPC_CREATE: 如果内核中不存在键值与key相等的消息队列，则新建一个消息队列:
 * 如果存在这样的消息队列，返回该消息队列的描述符。
 *      IPC_EXCL: 和IPC_CREATE一起使用，如果对应键值的消息队列已存在，则出错，返
 * -1，它单独使用并没有意义。
 *      如果调用成功返回一个消息对列的描述符，否则返回-1.
 *
 * int msgsnd(int msqid, struct msgbuf *msgp, size_t msgsz, int msgflg);
 * 用于向消息队列中写数据。
 * msgsnd的参数含义如下：
 *      msqid: 函数向msqid标识的消息队列发送一个消息；
 *      msgp : msgp指向要发送的消息；
 *      msgsz: 要发送消息的大小，不包含消息类型所占的4个字节
 *      msgflg:操作标志位，可以设置为0或IPC_NOWAIT.如果msgflg为0，则当消息队列已满
 * 已满的时候，msgsnd会阻塞，直到消息可以写进消息队列；如果msgflg为IPC_NOWAIT，当消
 * 息队列已满的时候，msgsnd函数将不等待立即返回。
 *      msgsnd调用成功返回0，失败返回-1，错误码写入errno，详情查看man手册
 */
int main()
{
    /*用户自定义消息缓冲*/
    struct mymsgbuf 
    {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;
    int qid; //消息队列描述符
    int msglen, msgkey;

    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1)
    {
        perror("ftok error!\n");
        exit(1);
    }
    
    if ((qid = msgget(msgkey, IPC_CREAT|0660)) == -1)
    {
        perror("msgget error!\n");
        exit(1);
    }
    printf("%d\n", qid);

    msgbuffer.msgtype = 3;
    strcpy(msgbuffer.ctrlstring, "hello, message queue!");
    msglen = sizeof(struct mymsgbuf) - 4;      
    if (msgsnd(qid, &msgbuffer, msglen, 0) == -1)
    {
        perror("msgsnd error!\n");
        exit(1);
    }

    return 0;
}


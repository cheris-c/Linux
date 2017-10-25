/*************************************************************************
  > File Name: recvmsg.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月26日 星期六 18时38分22秒
 ************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * #include <sys/msg.h>
 * int msgrcv(int msqid, struct msgbuf *msgp, size_t msgsz, long int msgtyp, int msgflg);
 * msgqid : 消息队列描述符
 * msgp   : 读取的消息存储到msgp指向的消息结构中
 * msgsz  : 消息缓冲区的大小
 * msgtyp : 请求读取的消息类型
 * msgflg : 操作标志位。msgflg可以为IPC_NOWAIT, IPC_EXCEPT, IPC_NOERROR
 *      IPC_NOWAIT ：如果没有满足条件的消息，调用立即返回，此时错误码为ENOMSG;
 *      IPC_EXCEPT : 与msgtyp配合使用，返回队列中第一个类型不为msgtyp的消息；
 *      IPC_NOERROR: 如果队列中满足条件的消息内容大于所请求的msgsz字节，则把该消息截断，
 * 截断部分将被丢弃。
 *      msgrcv函数成功后返回读出的实际字节数，否则返回-1。常见的错误码见man手册.
 */
#define BUF_SIZE  256
#define PROJ_ID   32
#define PATH_NAME "."

int main()
{
    struct mymsgbuf
    {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    }msgbuffer;
    int qid, msglen;
    key_t msgkey;

    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1)
    {
        perror("ftok error!\n");
        exit(1);
    }
    
    if((qid = msgget(msgkey, IPC_CREAT|0660)) == -1)
    {
        perror("msgget error!\n");
        exit(1);
    }

    msglen = sizeof(struct mymsgbuf) - 4;
    if (msgrcv(qid, &msgbuffer, msglen, 3, 0) == -1)
    {
        perror("msgrcv error\n");
        exit(1);
    }

    printf("Get message form %d : %s\n", qid, msgbuffer.ctrlstring);

    return 0;
}


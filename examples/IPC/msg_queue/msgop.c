/*************************************************************************
  > File Name: msgop.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月26日 星期六 20时34分36秒
 ************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
 * #include <sys/msg.h>
 * int msgctl(int msqid, int cmd, struct msqid_ds *buf);
 * msgctl系统调用对msqid标识的消息队列执行cmd操作，cmd操作有：
 *      IPC_STAT：该命令用来获取消息队列对应的msqid_ds数据结构，并将其保存到
 *      buf所指向的地址空间；
 *      IPC_SET：该命令用来设置消息队列的属性，要设置的属性存储在buf中，可设置
 *      的属性包括：msg_perm.uid、msg_perm.pid、msg_perm.mode以及msg_qbytes.
 *      IPC_RMID: 从内核中删除msqid标识的消息队列。
 */

#define PATH_NAME "."
#define BUF_SIZE  256
#define PROJ_ID   32

void getmsgattr(int msqid, struct msqid_ds msg_info);

int main()
{
    struct mymsgbuf
    {   
        long msgtype;
        char ctrlstring[BUF_SIZE];
    }msgbuffer;

    int qid, msglen;
    key_t msgkey;
    struct msqid_ds msq_attr;

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
    getmsgattr(qid, msq_attr); //输出消息队列的属性

    msgbuffer.msgtype = 2;
    strcpy(msgbuffer.ctrlstring, "Another message");
    msglen = sizeof(struct mymsgbuf) - 4;
    if (msgsnd(qid, &msgbuffer, msglen, 0) == -1)
    {
        perror("msgget error!\n");
        exit(1);
    }
    getmsgattr(qid, msq_attr);

    //设置消息队列的属性
    msq_attr.msg_perm.uid = 3;
    msq_attr.msg_perm.gid = 2;
    if (msgctl(qid, IPC_SET, &msq_attr) == -1)
    {
        perror("msg set error!\n");
        exit(1);
    }

    memset(&msq_attr, 0, sizeof(struct msqid_ds));
    getmsgattr(qid, msq_attr); //再次观察其属性
    //从内核中删除该消息队列
    if (msgctl(qid, IPC_RMID, NULL) == -1)
    {
        perror("msg rm error!\n");
        exit(1);
    }

    memset(&msq_attr, 0, sizeof(struct msqid_ds));
    getmsgattr(qid, msq_attr);

    return 0;
}

void getmsgattr(int msqid, struct msqid_ds msg_info)
{
    if (msgctl(msqid, IPC_STAT, &msg_info) == -1)
    {
        perror("msgctl error!\n");
        return;
    }

    printf("*********information of message queue%d**********\n", msqid);
    printf("last msgsnd to msqtime is %s", ctime(&(msg_info.msg_stime)));
    printf("last msgrcv time from msg is %s", ctime(&(msg_info.msg_rtime)));
    printf("last change msq time is %s", ctime(&(msg_info.msg_ctime)));
    printf("current number of bytes on queue is %d\n", msg_info.msg_cbytes);
    printf("number of messages in queue is %d\n", msg_info.msg_qnum);
    printf("max number of bytes on queue is %d\n", msg_info.msg_qbytes);
    printf("pid of last msgsnd is %d\n", msg_info.msg_lspid);
    printf("pid of last msgrcv is %d\n", msg_info.msg_lrpid);
    printf("msg uid is %d\n", msg_info.msg_perm.uid);
    printf("msg gid is %d\n", msg_info.msg_perm.gid);
    printf("*********information end!**************\n\n");
}

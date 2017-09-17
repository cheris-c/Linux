/*************************************************************************
  > File Name: server.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月27日 星期日 14时57分11秒
 ************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE    1024
#define PROJ_ID     32
#define PATH_NAME   "./tmp"
#define SERVER_MSG  1
#define CLIENT_MSG  2

/*
 *
 */

int main()
{
    struct mymsgbuf 
    {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    }msgbuffer;

    int qid, msglen;
    key_t msqkey;

    if ((msqkey = ftok(PATH_NAME, PROJ_ID)) == -1)
    {
        perror("ftok error!\n");
        exit(1);
    }

    if ((qid = msgget(msqkey, IPC_CREAT|0660)) == -1)
    {
        perror("msgget error!\n");
        exit(1);
    }

    while (1)
    {
        printf("server: ");
        fgets(msgbuffer.ctrlstring, BUF_SIZE, stdin);
        if (strcmp(msgbuffer.ctrlstring, "quit") == 0)
        {
            msgctl(qid, IPC_RMID, NULL);
            exit(1);
        }

        msgbuffer.ctrlstring[strlen(msgbuffer.ctrlstring)-1] = '\0';
        msgbuffer.msgtype = SERVER_MSG;
        if (msgsnd(qid, &msgbuffer, strlen(msgbuffer.ctrlstring)+1, 0) == -1)
        {
            perror("Server msgsnd error!\n");
            exit(1);
        }
    
        memset(&msgbuffer, 0, sizeof(struct mymsgbuf));
        if (msgrcv(qid, &msgbuffer, BUF_SIZE, CLIENT_MSG, 0) == -1)
        {
            perror("Server msgrcv error!\n");
            exit(1);
        }

        printf("Client: %s\n", msgbuffer.ctrlstring);
    }

    return 0;
}

/*************************************************************************
  > File Name: client.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月27日 星期日 15时29分26秒
 ************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_MSG 1
#define CLIENT_MSG 2
#define PATH_NAME  "./tmp"
#define BUF_SIZE   1024
#define PROJ_ID    32

int main()
{
    struct mymsgbuf
    {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;

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
        if (msgrcv(qid, &msgbuffer, BUF_SIZE, SERVER_MSG, 0) == -1)
        {
            perror("msgrcv error!\n");
            exit(1);
        }
        printf("Server: %s\n", msgbuffer.ctrlstring);
        
        printf("Client: ");
        memset(&msgbuffer, 0, sizeof(struct mymsgbuf));
        fgets(msgbuffer.ctrlstring, BUF_SIZE, stdin);
        if (strncmp(msgbuffer.ctrlstring, "quit", 4) == 0)
        {
            break;
        }

        msgbuffer.ctrlstring[strlen(msgbuffer.ctrlstring)-1] = '\0';
        msgbuffer.msgtype = CLIENT_MSG;
        if (msgsnd(qid, &msgbuffer, strlen(msgbuffer.ctrlstring) + 1, 0) == -1)
        {
            perror("client msgsnd error!\n");
            exit(1);
        }
    }



    return 0;
}


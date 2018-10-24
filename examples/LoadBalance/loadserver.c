/*************************************************************************
  > File Name: loadserver.c
  > Description: load balance server 
  > Author: Actually
  > Created Time: Wed 05 Sep 2018 08:57:03 PM EDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

int port[] = {6000, 7000, 8000, 9000};
int serverSet_len = sizeof(port)/sizeof(port[0]);

int serverfd[4];
int cli;
int sockfd_ser;

void* pthread_run(void *arg);
void  add_server();

int main() 
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in s_addr, c_addr;
    memset(&s_addr, 0, sizeof(s_addr));

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(6001);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    add_server();

    int res = bind(sockfd, (struct sockaddr*)&s_addr, sizeof(s_addr));
    assert(res != -1);

    res =  listen(sockfd, 5);
    assert(res != -1);

    while(1)
    {
        socklen_t len = sizeof(c_addr);
        cli = accept(sockfd, (struct sockaddr*)&c_addr, &len);
        assert(cli != -1);

        printf("accept = %d\n", cli);

        static int i = 0;
        if (i == 4)
        {
            i = 0;
        }

        sockfd_ser = serverfd[i++];//选择某一服务器sockfd

        pthread_t threadId;
        pthread_create(&threadId, NULL, pthread_run, NULL);
    }

    close(sockfd);

    return 0;
}

void add_server()
{
    int i;

    for(i = 0;i < serverSet_len; ++i)
    {
        int sockfdser = socket(AF_INET,SOCK_STREAM,0);
        assert(sockfdser != -1);
        struct sockaddr_in saddr;
        memset(&saddr,0,sizeof(saddr));

        saddr.sin_family = AF_INET;
        printf("port = %d\n", port[i]);
        saddr.sin_port = htons(port[i]);

        saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        int res = connect(sockfdser,(struct sockaddr*)&saddr,sizeof(saddr));
        assert(res != -1);
        serverfd[i] = sockfdser;//保存每一个服务器sockfd（轮寻选择） 
    }
}

void *pthread_run(void *arg)
{
    while(1)
    {
        char buff[128] = {0};
        int n = recv(cli, buff, 127, 0);

        printf("buff = %s\n", buff);
        send(sockfd_ser, buff, strlen(buff), 0);//将客户端发送的消息转发给对应的服务器发送消息
        
        if(strncmp(buff, "end", 3) == 0)
        {
            break;
        }

        memset(buff, 0, 128);
        recv(sockfd_ser, buff, 127, 0);//接收到服务端"ok" 
        send(cli, buff, strlen(buff), 0);//转发给客户端
    }
}

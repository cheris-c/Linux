/*************************************************************************
  > File Name: server.c
  > Description: A server file for load balancing. 
  > Author: Actually
  > Created Time: Wed 05 Sep 2018 10:36:39 AM EDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void* pthread_run(void *arg) 
{
    int cli = *((int*)arg);
    while(1)
    {
        char buff[128] = {0};
        int n = recv(cli, buff, 127, 0);

        printf("buff = %s\n", buff);
        send(cli, "ok", 2, 0);
    }
}

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in s_addr, c_addr;
    memset(&s_addr, 0, sizeof(s_addr));
 
    unsigned short int port = atoi(argv[1]);

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    printf("port = %d\n", port);

    int res = bind(sockfd, (struct sockaddr*)&s_addr, sizeof(s_addr));
    assert(res != -1);

    listen(sockfd, 5);

    while(1) 
    {
       socklen_t len = sizeof(c_addr);
       int cli = accept(sockfd, (struct sockaddr*)&c_addr, &len);
       assert(cli != -1);

       printf("accept = %d\n", cli);

       //启动线程
       pthread_t threadid;
       pthread_create(&threadid, NULL, pthread_run, (void*)(&cli));
    }
    
    close(sockfd);

    return 0;
}


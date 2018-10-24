/*************************************************************************
  > File Name: client.c
  > Description: A client for Load balancing.
  > Author: Actually
  > Created Time: Wed 05 Sep 2018 11:00:15 AM EDT
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(6001);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = connect(sockfd, (struct sockaddr*)&s_addr, sizeof(s_addr));
    assert(res != -1);

    while (1)
    {
        printf("input:: \n");
        char buff[128] = {0};
        fgets(buff, 128, stdin);

        send(sockfd, buff, strlen(buff), 0);
        if(strncmp(buff, "end", 3) == 0)
        {
            break;
        }

        memset(buff, 0, 128);
        recv(sockfd, buff, 127, 0);
        printf("%s\n", buff);
    }

    close(sockfd);

    return 0;
}

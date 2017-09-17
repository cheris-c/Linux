/*************************************************************************
  > File Name: client.c
  > Description: It's a simple client completly via named pipe`  
  > Author: Actually
  > Created Time: 2017年08月25日 星期五 13时41分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_READ  "writefifo"
#define FIFO_WRITE "readfifo"
#define BUF_SIZE   1024

int main()
{
    int wfd, rfd;
    char buf[BUF_SIZE];
    int len;

    umask(0);
    if (mkfifo(FIFO_WRITE, S_IFIFO|0666))
    {
        printf("Can't create FIFO %s because %s!\n", FIFO_WRITE, strerror(errno));
        exit(1);
    }

    while ((rfd = open(FIFO_READ, O_RDONLY)) == -1)
    {
        sleep(1);
    }

    wfd = open(FIFO_WRITE, O_WRONLY);
    if (wfd == -1)
    {
        printf("Fail to open FIFO %s: %s!\n", FIFO_WRITE, strerror(errno));
        exit(-1);
    }

    while (1)
    {
        len = read(rfd, buf, BUF_SIZE);
        if (len > 0)
        {
            buf[len] = 0;
            printf("server: %s\n", buf);
        }

        printf("client: ");
        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf)-1] = '\0';
        if (strncmp(buf, "quit", 4) == 0)
        {
            close(wfd);
            unlink(FIFO_WRITE);
            close(rfd);
            exit(0);
        }

        write(wfd, buf, strlen(buf));
    }

    return 0;
}

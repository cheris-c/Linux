/*************************************************************************
  > File Name: server.c
  > Description: It's a simple server completely via named pipe 
  > Author: Actually
  > Created Time: 2017年08月25日 星期五 11时18分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_READ  "readfifo"
#define FIFO_WRITE "writefifo"
#define BUF_SIZE   1024

int main()
{
    int wfd, rfd;
    char buf[BUF_SIZE];
    int len;

    umask(0);
    if (mkfifo(FIFO_WRITE, S_IFIFO | 0666) == -1)
    {
        perror("mkfifo error!\n");
        exit(1);
    }

    umask(0);
    wfd = open(FIFO_WRITE, O_WRONLY);
    if (wfd == -1)
    {
        printf("open FIFO %s error: %s\n", FIFO_WRITE, strerror(errno));
        exit(1);
    }

    while((rfd = open(FIFO_READ, O_RDONLY)) == -1)
    {
        sleep(1);
    }

    while (1)
    {
        printf("server: ");
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

        memset(buf, '\0', BUF_SIZE);
        len = read(rfd, buf, BUF_SIZE);
        if (len > 0)
        {
            buf[len] = '\0';
            printf("client: %s\n", buf);
        }
    }

    return 0;
}

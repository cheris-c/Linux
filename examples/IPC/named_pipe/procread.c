/*************************************************************************
  > File Name: procread.c
  > Description: read from named pipe which is named myinfo 
  > Author: Actually
  > Created Time: 2017年08月24日 星期四 22时04分09秒
 ************************************************************************/

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define FIFO_NAME "myfifo"

int main()
{
    int fd;
    char buf[BUF_SIZE];

    umask(0);
    fd = open(FIFO_NAME, O_RDONLY);
    read(fd, buf, BUF_SIZE);
    printf("Read content: %s\n", buf);
    close(fd);
    return 0;
}

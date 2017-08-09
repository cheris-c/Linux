/*************************************************************************
    > File Name: socketop.h
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 08:28:31 AM CST
 ************************************************************************/

#ifndef SOCKETOP_H
#define SOCKETOP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

int socket_create(int port);
void socket_accept(int st, void* (*callback)(void *arg)/*线程处理函数*/);


void sockaddr_toa(const struct sockaddr_in *addr, char *IPAddr);


#endif  /*SOCKETOP_H*/

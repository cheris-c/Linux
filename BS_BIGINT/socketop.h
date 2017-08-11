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
#include <assert.h>

#include <signal.h>
#include <pthread.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <sys/epoll.h>

#define MAX_EVENT_NUMBER 1024

int socket_create(int port);
//用于处理信号的管道，以实现统一事件源
static int sig_pipefd[2];

void socket_accept(int st, void* (*callback)(void *arg)/*线程处理函数*/);


void sockaddr_toa(const struct sockaddr_in *addr, char *IPAddr);
void addfd(int epollfd, int fd);
void removefd(int epollfd, int fd);

void sig_handler(int sig);
void addsig(int sig, void (handler)(int), bool restart = true);
void setup_sig_pipe(int epollfd);
int setnonblocking(int fd);

#endif  /*SOCKETOP_H*/

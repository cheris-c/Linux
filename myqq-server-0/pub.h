/*
 * pub.h
 *
 *  Created on: 2013年12月17日
 *      Author: zhujy
 */

#ifndef PUB_H_
#define PUB_H_


void setdaemon();
void catch_Signal(int Sign);
int signal1(int signo, void (*func)(int));
int socket_create(int port);
int socket_accept(int listen_st);
int setnonblocking(int st);//将socket设置为非阻塞

#endif /* PUB_H_ */

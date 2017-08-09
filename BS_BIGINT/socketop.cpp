/*************************************************************************
    > File Name: socketop.cpp
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 08:28:44 AM CST
 ************************************************************************/

#include "socketop.h"

int socket_create(int port)//根据参数port，建立server端socket
{
	int st = socket(AF_INET, SOCK_STREAM, 0);//建立TCP的socket描述符
	if (st == -1)
	{
		printf("socket failed %s\n", strerror(errno));
		return 0;
	}

	int on = 1;
	if (setsockopt(st, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
	{
		printf("setsockopt failed %s\n", strerror(errno));
		return 0;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(st, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		printf("bind failed %s\n", strerror(errno));
		return 0;
	}

	if (listen(st, 100) == -1)
	{
		printf("listen failed %s\n", strerror(errno));
		return 0;
	}

	printf("listen %d success\n", port);
	return st;//返回listen的socket描述符
}

void sockaddr_toa(const struct sockaddr_in *addr, char *IPAddr)//将struct sockaddr_in转化为IP地址字符串
{
	unsigned char *p = (unsigned char *)&(addr->sin_addr.s_addr);
	sprintf(IPAddr, "%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
}

void socket_accept(int st, void* (*callback)(void *arg)/*线程处理函数*/)
{
	pthread_t thr_d;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//设置线程为可分离状态

	int client_st = 0;
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	
	while (1)//循环执行accept
	{
		memset(&client_addr, 0, sizeof(client_addr));
		//accept函数阻塞，直到有client端连接到达，或者accept错误返回
		client_st = accept(st, (struct sockaddr *)&client_addr, &len);

		if (client_st == -1)
		{
			printf("accept failed %s\n", strerror(errno));
			break;//accept错误，循环break
		} else
		{
			char sIP[32];
			memset(sIP, 0, sizeof(sIP));
			sockaddr_toa(&client_addr, sIP);
			printf("accept by %s\n", sIP);
			int *tmp = (int *)malloc(sizeof(int));
			*tmp = client_st;
			{
				//将来自client端的socket做为参数，启动一个可分离线程
				pthread_create(&thr_d, &attr, callback, tmp);
			}
		}
		
	}
	pthread_attr_destroy(&attr);
}



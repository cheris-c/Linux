/*************************************************************************
    > File Name: main.cpp
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 08:26:42 AM CST
 ************************************************************************/

#include "utili.h"
#include "handlehttp.h"
#include "socketop.h"

void* socket_control(void *arg);

int main(int argc, char *args[])
{	
	if (argc < 2)//如果没有参数，main函数返回
	{
		printf("usage:no server port!\n");
		return EXIT_FAILURE;
	}

	int iport = atoi(args[1]);//将第一个参数转化为整数
	if (iport == 0)
	{
		printf("port %d is invalid\n", iport);
		return EXIT_FAILURE;
	}

	int st = socket_create(iport);//建立socket
	if (st == 0)
		return EXIT_FAILURE;
	
	printf("myhttp is begin\n");
	//setdaemon();//设置进程为daemon状态
	//signal1(SIGINT, catch_Signal);	//捕捉SIGINT信号	
	socket_accept(st, socket_control);
	
	close(st);	
	printf("myhttp is end\n");
	
	return EXIT_SUCCESS;
}

void* socket_control(void *arg)
{
	printf("thread is begin\n");
	int st = *(int *) arg;//得到来自client端的socket
	free((int *) arg);

	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	ssize_t rc = recv(st, buf, sizeof(buf), 0);//接收来自client端socket的消息
	if (rc <= 0)
	{
		printf("recv failed %s\n", strerror(errno));
	} else
	{
		printf("recv:\n%s", buf);
		char command[1024];
		memset(command, 0, sizeof(command));
		gethttpcommand(buf, command); //得到http 请求中 GET后面的字符串

		char *content = NULL;
		size_t ilen = make_http_content(command, &content);//根据用户在GET中的请求，生成相应的回复内容
		if (ilen > 0)
		{
			send(st, content, ilen, 0);//将回复的内容发送给client端socket
			free(content);
		}
	}
	close(st);//关闭client端socket
	printf("thread_is end\n");
	return NULL;
}




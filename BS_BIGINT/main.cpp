/*************************************************************************
    > File Name: main.cpp
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 08:26:42 AM CST
 ************************************************************************/

#include "utili.h"
#include "handlehttp.h"
#include "socketop.h"

void* socket_control(void *arg);
void setdaemon();

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
	setdaemon();//设置进程为daemon状态
	socket_accept(st, socket_control);
	
	close(st);	
	printf("myhttp is end\n");
	
	return EXIT_SUCCESS;
}

void* socket_control(void *arg)
{
    int st = *(int *)arg; //得到来自服务端socket

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    bzero(&client_addr, sizeof(client_addr));
    int client_st = accept(st, (struct sockaddr *)&client_addr, &len); //获取client端的socket

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd, client_st);
    setup_sig_pipe(epollfd);
    
    bool stop_server = false;
    while (!stop_server)
    {
	int num = epoll_wait(epollfd, events, MAX_EVENT_NUMBER,-1);
	if (num<0 && errno!=EINTR)
	{
	    printf("epoll failure\n");
	    break;
	}

	for (int i=0; i < num; ++i)
	{
	    int fd = events[i].data.fd;
	    if (fd == client_st && events[i].events & EPOLLIN)
	    {
		char buf[BUFSIZE];
		memset(buf, 0, sizeof(buf));
		size_t rc = recv(client_st, buf, sizeof(buf),0);
		if (rc <= 0)
		{
		    printf("recv failed %s\n", strerror(errno));
		    continue;
		}
		else
		{
		    printf("recv:\n%s", buf);
		    char command[1024];
		    memset(command, 0, sizeof(command));
		    gethttpcommand(buf, command); //得到http 请求中 GET后面的字符串

		    char *content = NULL;
		    size_t ilen = make_http_content(command, &content);//根据用户在GET中的请求，生成相应的回复内容
		    if (ilen > 0)
		    {
			send(client_st, content, ilen, 0);//将回复的内容发送给client端socket
			free(content);
			content = NULL;
		    }
		 } //else
	    } //if (events[i].events & EPOLLIN)
	    else if (fd == sig_pipefd[0] && events[i].events & EPOLLIN)
	    {
		int siig;
		char signals[1024];
		int ret = recv(sig_pipefd[0], signals, sizeof(signals), 0);
		if (ret <= 0)
		{
		    continue;
		}
		else
		{
		    for (int i = 0; i < ret; ++i)
		    {
			switch(signals[i])
			{
			    case SIGTERM:
			    case SIGINT:
			    {
				stop_server = true;
				break;
			    }
			    default:
			    {
				break;
			    }
    		}//switch
		    }//for
		}//else
	    }//else if
	}//for

    /*
	printf("thread is begin\n");
	int st = *(int *) arg;//得到来自client端的socket
	free((int *) arg);

	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	size_t rc = recv(st, buf, sizeof(buf), 0);//接收来自client端socket的消息
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
    */
    }
    
    close(epollfd);
    close(client_st);
    return NULL;
}

void setdaemon()
{
	pid_t pid, sid;
	pid = fork();
	if (pid < 0)
	{
		printf("fork failed %s\n", strerror(errno));
		exit (EXIT_FAILURE);
		;
	}
	if (pid > 0)
	{
		exit (EXIT_SUCCESS);
	}

	if ((sid = setsid()) < 0)
	{
		printf("setsid failed %s\n", strerror(errno));
		exit (EXIT_FAILURE);
	}

	/*
	 if (chdir("/") < 0)
	 {
	 printf("chdir failed %s\n", strerror(errno));
	 exit(EXIT_FAILURE);
	 }
	 umask(0);
	 close(STDIN_FILENO);
	 close(STDOUT_FILENO);
	 close(STDERR_FILENO);
	 */
}




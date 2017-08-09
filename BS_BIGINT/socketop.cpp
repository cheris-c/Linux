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

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);

    return old_option;
}

void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void sig_handler(int sig)
{
    int save_errno = errno;
    int msg = sig;
    send(sig_pipefd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}

void addsig(int sig, void (handler)(int), bool restart)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = handler;
    if (restart)
    {
	sa.sa_flags |= SA_RESTART;
    }

    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

void setup_sig_pipe(int epollfd)
{
    assert(epollfd != -1);
    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sig_pipefd);
    assert(ret != -1);

    setnonblocking(sig_pipefd[1]);
    addfd(epollfd, sig_pipefd[0]);

    /*设置信号处理函数*/
    addsig(SIGTERM, sig_handler);
    addsig(SIGINT, sig_handler);
    addsig(SIGPIPE, SIG_IGN);
}

void socket_accept(int st, void* (*callback)(void *arg)/*线程处理函数*/)
{
	pthread_t thr_d;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//设置线程为可分离状态
	
    	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd = epoll_create(5);
	assert(epollfd != -1);
	addfd(epollfd, st);
	setup_sig_pipe(epollfd);
    
	bool stop_server = false;
	while (!stop_server)//循环执行accept
	{
		int num = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);

		if (num<0 && errno!=EINTR)
		{
		    printf("epoll failure\n");
		    break;
		}

		for (int i = 0; i < num; i++)
		{
		    int sockfd = events[i].data.fd;
		    /*如果就绪的文件描述符是监听的描述符，则处理新的连接*/
		    if (sockfd == st)
		    {	
			pthread_create(&thr_d, &attr, callback, (void *)&st);
			//addfd(epollfd, connfd);
		    }
		    else if (sockfd == sig_pipefd[0] && events[i].events & EPOLLIN)  
		    {
			int sig;
			char signals[1024];
			int ret = recv(sig_pipefd[0], signals, sizeof(signals), 0);
			if (ret <= 0)
			{
			    printf("recv failed %s\n", strerror(errno));
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
		if (client_st == -1)
		{
			pirintf("accept failed %s\n", strerror(errno));
			break;		    //accept错误，循环break
		} else
		{
			char sIP[32];
			memset(sIP, 0, sizeof(sIP));
			sockaddr_toa(&client_addr, sIP);
			printf("accept byi %s\n", sIP);
			int *tmp = (int *)malloc(sizeof(int));
			*tmp = client_st;
			{
				//将来自client端的socket做为参数，启动一个可分离线程
				pthread_create(&thr_d, &attr, callback, tmp);
			}
		}
		*/
	}
	close(epollfd);
	pthread_attr_destroy(&attr);
}



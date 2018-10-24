#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXDATASIZE 100
#define PORT 8111

int main()
{
	int sockfd;
	struct sockaddr_in addrSer, addrCli;
	socklen_t addrlen;
	int num;
	char recvbuf[MAXDATASIZE], sendbuf[MAXDATASIZE];

	int optval = 1;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("func socket error!\n");
		exit(-1);
	}

	bzero(&addrSer, sizeof(addrSer));
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(PORT);
	addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(sockfd, (struct sockaddr *)&addrSer, sizeof(addrSer))== -1)
	{
		perror("func bind error!\n");
		close(sockfd);
		exit(-1);
	}


	addrlen = sizeof(addrSer);
	while(1)
	{
		num = recvfrom(sockfd, recvbuf, MAXDATASIZE, 0, (struct sockaddr*)&addrCli, &addrlen);
		if (num < 0)
		{
			perror("func recvform() error!\n");
			exit(-1);
		}

		recvbuf[num] = '\0';
		printf("Cli-> %s\n",recvbuf);

		printf("Ser->");
		scanf("%s", sendbuf);
		if (strcmp(sendbuf, "quit") == 0)
			break;
		sendto(sockfd, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrCli, addrlen);
	}

	close(sockfd);

	return 0;
}

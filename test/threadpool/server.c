#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>

#include "threadpool.h"
#define THREAD_NUM 10
#define BUFSIZE 1024
void *func(void *arg)
{
	int sockfd = (int)arg;
	int n;
	char buf[BUFSIZE];
	bzero(buf,BUFSIZE);

	if(sockfd<0)
	{
		printf("accept failed.\n");
		exit(1);
	}
	while((n=read(sockfd,buf,BUFSIZE))>0)
	{
		printf("sockfd:%d\n",sockfd);
		usleep(400000);
		char *newbuf=malloc(1024);
		write(sockfd,buf,n);
		free(newbuf);
	}
	if(n<0)
	{
		printf("read failed.\n");
	}
	close(sockfd);
}
int main()
{
	if (tpool_create(THREAD_NUM) != 0) {
	printf("tpool_create failed\n");
	exit(1);
	}

	int sock_serv,sockfd;
	struct sockaddr_in servaddr,clientaddr;
	bzero(&servaddr,sizeof(servaddr));
	
	sock_serv = socket(AF_INET,SOCK_STREAM,0);
	if(sock_serv<0)
	{
		printf("server socket init failed.\n");
		exit(1);
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8987);
	int ret =inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
	if(ret==0)
	{
		printf("invalid address.\n");
		exit(1);
	}
	else if (ret==-1)
	{
		printf("address cast failed.\n");
		exit(1);
	}
	
	ret = bind(sock_serv,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret<0)
	{
		printf("bind failed.\n");
		exit(1);
	}

	ret = listen(sock_serv,5);
	

	if(ret<0)
	{
		printf("listen failed.\n");
		exit(1);
	}
	
	int clientlen = sizeof(clientaddr);
	int n;
	for(;;)
	{
		sockfd =accept(sock_serv,(struct sockaddr *)&clientaddr,&clientlen);
		tpool_add_work(func, (void*)sockfd);
	}
}

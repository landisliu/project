#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
int main()
{
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
	int bufsize = 256;
	char buf[bufsize];
	int n;
	for(;;)
	{
		sockfd =accept(sock_serv,(struct sockaddr *)&clientaddr,&clientlen);
		if(sockfd<0)
		{
			printf("accept failed.\n");
			exit(1);
		} 
		while((n=read(sockfd,buf,bufsize))>0)
		{
			write(sockfd,buf,n);
		}
		if(n<0)
		{
			printf("read failed.\n");
		}
		close(sockfd);
	}
}

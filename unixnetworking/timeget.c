#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/tyeps.h>
int main(int argc,char ** argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("init socket failed.\n");
		exit(1);
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	int ret = inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
	if(ret>0)
	{
		printf("address cast success.\n");
	}
	else if(ret<0)
	{
		printf("address cast error.\n");
		exit(1);
	}
	else if(ret==0)
	{
		printf("invalid address.\n");
		exit(1);
	}
	
	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret<0)
	{
		printf("connect to server failed.\n");
	}
	
	int buflength = 1024;
	char buf[buflength];
	while((n=read(sockfd,buf,buflength))>0)
	{
		buf[n]= 0;
		if(fputs(buf,stdout)==EOF)
		{
			printf("output to stdout failed.\n");
			exit(1);
		}
	}
	if(n<0)
	{
		printf("read from server failed.\n");
		exit(1);
	}
	exit(0);
}


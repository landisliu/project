#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<limits.h>
#include<sys/socket.h>
#include<netinet/in.h>
void str_echo(int);
int main()
{
	int listenfd,connfd;
	struct sockaddr_in clientaddr,servaddr;
	socklen_t clilen;
	pid_t childpid;
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8978);
	
	int ret =bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret!=0)
	printf("bind failed\n");
	else
	printf("bind success\n");
	ret =listen(listenfd,5);
	if(ret !=0)
	printf("listen failed\n ");
	
	for(;;)
	{
		clilen = sizeof(clientaddr);
		connfd = accept(listenfd,NULL,NULL);
		if(connfd<0)
			printf("accept failed.\n");
		else
			printf("accept success\n");
		if((childpid = fork())==0)
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}

void str_echo(int sockfd)
{
	printf("in deal process\n");
	int n;
	char buf[40];
	n=read(sockfd,buf,sizeof(buf));
	printf("read %d bytes,%s",n,buf);
	int ret = write(sockfd,buf,n);
	printf("write %d bytes",ret);
}

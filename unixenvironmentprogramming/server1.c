#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#define BUFSIZE 1024

int main(int argc,char * argv[])
{
	int servfd,clientfd;
	struct sockaddr_in serv_addr,client_addr;

	if((servfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("create server socket error.\n");
		exit(1);
	}
	
	if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<0)
	{
		printf("parse address failed.\n");
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8899);  
	
	if(bind(servfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("bind faild.\n");
		exit(1);
	}
	
	if(listen(servfd,5)<0)
	{
		printf("listen failed.\n");
		exit(1);
	}
	
	if((clientfd =accept(servfd,NULL,NULL))<0)
	{
		printf("accept failed.\n");
		exit(1);
	}
	char buf[BUFSIZE];

	if(read(clientfd,buf,sizeof(buf))>0)
	{
		printf("read from client:%s\n",buf);
		exit(1);
	}
}

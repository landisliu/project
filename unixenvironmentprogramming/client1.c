#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main(int argc,char * argv[])
{
	int servfd,clientfd;
	struct sockaddr_in serv_addr,client_addr;

	if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<0)
	{
		printf("parse address failed.\n");
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8899);  


	if((clientfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("create client socket error.\n");
		exit(1);
	}

	
	if(connect(clientfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("connect failed.\n");
		exit(1);
	}
	
	char *c ="hello world";
	if(write(clientfd,c,strlen(c)+1)!=strlen(c)+1)
	{
		printf("write failed.\n");
		exit(1);
	}
	exit(0);
}

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#define BUFFERSIZE 1024

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
	while(1)
	{
		printf("get accept\n");
		if((clientfd =accept(servfd,NULL,NULL))<0)
		{
			printf("accept failed.\n");
			exit(1);
		}
		char buf[BUFFERSIZE];
		FILE * f = fopen("tf","w");
		int n;
		while((n=read(clientfd,buf,BUFFERSIZE))>0)
		{
			printf("content to read:%s\n",buf);
			if(write(fileno(f),buf,n)!=n)	
			{
				printf("write to tf file failed.\n");
				exit(1);
			}
		}
		if(feof(f))
		{
			printf("reach the end of file.\n");
		}
		if(ferror(f))
			printf("error happend on file\n");
		fclose(f);
	}
	exit(0);
}

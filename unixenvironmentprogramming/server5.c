#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>
#define BUFFERSIZE 256

void chldfunc(int sig)
{
	wait(NULL);
}
int main(int argc,char * argv[])
{
	
	signal(SIGCHLD,chldfunc);
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
	char buf[BUFFERSIZE];
	int n;
	char filename[256];
	while(1)
	{
		if((clientfd =accept(servfd,NULL,NULL))<0)
		{
			printf("accept failed.\n");
			exit(1);
		}
		pid_t pid;
		if((pid=fork())>0)//parent
		{
			close(clientfd);
			continue;
		}
		else if(pid==0) //child
		{
			bzero(filename,256);
			bzero(buf,BUFFERSIZE);
			n=0;
			if((n=recv(clientfd,buf,BUFFERSIZE,0))>0)
			{
				buf[strlen(buf)] = 0;
				strcpy(filename,buf);
			}

			FILE * f = fopen(filename,"r");
			if(f==NULL)
			{
				printf("open file failed.\n");
				exit(1);
			}

			bzero(buf,BUFFERSIZE);

			while((n=fread(buf,1,BUFFERSIZE,f))>0)
			{
				if((n=send(clientfd,buf,BUFFERSIZE,0))<0)
				{
					printf("send failed.\n");
					exit(1);
				}			
			}	
			fclose(f);
			close(clientfd);
			exit(0);
			
		}
		else
		{
			printf("fork failed.\n");
			exit(1);
		}
	}
	exit(0);
}

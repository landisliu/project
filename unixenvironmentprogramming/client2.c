#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define BUFFERSIZE 1024
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

	char str[BUFFERSIZE];
	FILE *fp = fopen("./tmpfile","r");

	if(fp==NULL)
	{
		printf("open file failed.\n");
		exit(1);
	}

	while(fgets(str,BUFFERSIZE,fp)!=NULL)
	{
		int len = strlen(str);
		printf("lines:%s\n",str);
		if(write(clientfd,str,len)!=len)
		{
			printf("write failed.\n");
			exit(1);
		}
	}

	fclose(fp);

	exit(0);
}

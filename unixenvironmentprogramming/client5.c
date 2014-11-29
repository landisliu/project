#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define BUFFERSIZE 256
int main(int argc,char * argv[])
{
	time_t t1,t2;
	if(argc!=3)
		exit(1);
	time(&t1);
	printf("%s,start time:%d\n",argv[2],t1);
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
	strcpy(str,argv[1]);
	printf("get %s from server.\n",str);
	int n;
	if((n=send(clientfd,str,BUFFERSIZE,0))<0)
	{
		printf("send request failed.\n");
		exit(1);
	}
	
	printf("saved as %s,local",argv[2]);

	FILE *fp = fopen(argv[2],"w");

	if(fp==NULL)
	{
		printf("open file failed.\n");
		exit(1);
	}

	bzero(str,BUFFERSIZE);
	while((n=recv(clientfd,str,BUFFERSIZE,0))>0)
	{
		if(fwrite(str,1,n,fp)!=n)
		{
			printf("save data to local failed.\n");
			exit(1);
		}
	}

	fclose(fp);
	time(&t2);
	printf("%s,end time:%d\n",argv[2],t2);
	exit(0);
}

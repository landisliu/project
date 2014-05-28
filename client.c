#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
int main()
{
	int sockserv,sockclient;
	sockserv = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8978);
	servaddr.sin_addr.s_addr= inet_addr("127.0.0.1");
	
	printf("init finished.");
	
	int ret  = connect(sockserv,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret<0)
	{	
		printf("connect failed.");
		exit(1);
	}
	char send[40];
	char recv[40];
	fgets(send,sizeof(send),stdin);
	
	printf("connect success");
	ret=write(sockserv,send,strlen(send));
	printf("write %d bytes\n",ret);
	ret = read(sockserv,recv,sizeof(recv));
	printf("receive %d bytes\n",ret);
	printf("%s\n",recv);
	close(sockserv);
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
int main()
{
	setbuf(stdout,NULL);
	setbuf(stdin,NULL);
	setbuf(stderr,NULL);
	int sockfd,n;
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8987);
	int ret = inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
	if(ret>0)
		printf("address cast success.\n");
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret>0)
		printf("connect success.\n");
	
	int bufsize = 256;
	char buf[bufsize];
	while(1)
	{
	sleep(1);
	strcpy(buf,"hello world!");
	n = write(sockfd,buf,strlen(buf));
	if(n>0)
	printf("write %d bytes.\n",n);
	n = read(sockfd,buf,bufsize);
	if(n>0)
	{
		printf("read %d bytes.\n",n);
		printf("%s\n",buf);
	}
	if(n<0)
	{
		printf("read error!\n");
		exit(1);
	}
	}	
	exit(0);
}

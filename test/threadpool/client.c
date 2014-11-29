#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include <pthread.h>
pthread_barrier_t pbt;
void * sendrequest(void *arg)
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
	//while(1)
	
	//sleep(1);
	clock_t t1,t2;
	t1 = clock();
	strcpy(buf,"hello world!");
	n = write(sockfd,buf,strlen(buf));
	if(n>0)
	//printf("write %d bytes.\n",n);
	n = read(sockfd,buf,bufsize);
	if(n>0)
	{
		t2 = clock();
		printf("time elapsed:%ld\n",t2-t1);
		//printf("read %d bytes.\n",n);
		//printf("%s\n",buf);
	}
	if(n<0)
	{
		perror("read error!");
		exit(1);
	}
		
	pthread_exit(NULL);
	pthread_barrier_wait(&pbt);
}
int main(int argc,char * argv[])
{
	
	if(argc<2)
		return 0;
	int client_count = atoi(argv[1]);
	int i=0;

	pthread_barrier_init(&pbt,NULL,client_count+1);
	pthread_t pts[client_count];
	for(i=0;i<client_count;i++)
	{
		if(pthread_create(pts+i,NULL,sendrequest,NULL)!=0)
		{
			perror("create thread failed.");
			exit(1);
		}
	}
	pthread_barrier_wait(&pbt);
	pthread_barrier_destroy(&pbt);
	exit(0);
}

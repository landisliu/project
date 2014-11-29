#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/epoll.h>
#define POLLSIZE 112
int main(int argc,char *argv[])
{

	int i=0;
	int epfd = epoll_create(POLLSIZE);
	if(epfd<0)
	{
		printf("create epoll failed.\n");
		exit(1);
	}
	FILE * file = fopen("./tmpfile","w+");
	if(file==NULL)
	{
		printf("can not open or create this file.\n");
		exit(1);
	}
	int fd = fileno(file);
	printf("%d\n",fd);
	struct epoll_event ee;
	ee.events = EPOLLIN;
	ee.data.fd = 0;
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,0,&ee)<0)
	{
		perror("add fd to epoll failed.");
		exit(1);
	}
	i++;
	struct epoll_event events[i];
	while(1)
	{
		int ret = epoll_wait(epfd,events,1,-1);
	
		if(ret>0)
		{
			for(i=0;i<ret;i++)
			{
				if(events[i].events & EPOLLIN)
				{

					printf("fd can be read.\n");
					int n;
					char buf[1024];
					while((n=read(events[i].data.fd,buf,1024))>0)
					{
						write(STDOUT_FILENO,buf,n);
					}
				}
			}
		}
	}
	exit(0);
}

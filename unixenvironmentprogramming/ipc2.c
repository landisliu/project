#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define BUFSIZE 1024
int main(int argc,char * argv)
{
	int fd[2];

	if(pipe(fd)<0)
	{
		printf("create pipe failed.\n");
		exit(1);
	}
	
	pid_t pid;
	if((pid=fork())<0)
	{
		printf("can not fork child process.\n");
		exit(1);
	}
	else if(pid>0) //parent
	{
		int n;
		close(fd[0]);
		char buf[BUFSIZE];
		bzero(buf,BUFSIZE);
		
		while((n=read(STDIN_FILENO,buf,BUFSIZE))>0)
		{
			write(fd[1],buf,n);
		}
		close(fd[1]);
		Wait(NULL);
	}
	else
	{
		close(fd[1]);
		int n;
		char buf[BUFSIZE];
		bzero(buf,BUFSIZE);
		if(fd[0]!=STDIN_FILENO)
		{
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
		}
		execl("/bin/more","more",(char *)0);
	}

	exit(0);	
}

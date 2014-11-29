#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

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
		close(fd[1]);
		int n;
		char buf[1024];
		bzero(buf,1024);
		if((n=read(fd[0],buf,1024))>0)
		{
			//write(STDOUT_FILENO,buf,n);
			printf("read from child %s",buf);
		}

	}
	else
	{
		close(fd[0]);
		char *msg = "hello world\n";
		write(fd[1],msg,12);
		
	}

	exit(0);	
}

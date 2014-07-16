#include"helper.h"
#include<sys/wait.h>
#define BUFFSIZE 256
int main(int argc,char * argv[])
{
	char buf[BUFFSIZE];
	pid_t pid;
	int status;

	printf("%%");
	while(fgets(buf,BUFFSIZE,stdin)!=NULL)
	{
		if(buf[strlen(buf)-1]=='\n')
		{
			buf[strlen(buf)-1]=0;
		}
		if((pid=fork())<0)
			err_quit("fork failed.");
		if(pid==0)
		{
			execlp(buf,buf,(char *)0);
			err_quit("exec failed.");
		}
		if(pid=waitpid(pid,&status,0)<0)
		{
			err_quit("wait failed.");
		}
		printf("%%");
	}
	exit(0);
}


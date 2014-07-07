#include "helper.h"
#include<signal.h>
int main(int argc,char * argv[])
{
	pid_t pid;
	int status;
	
	if((pid=fork())<0)
		err_quit("fork error.");
	else if(pid==0)
		exit(7);
	
	if(wait(&status)!=pid)
		err_quit("wait error.");
	pr_exit(status);

	
	if((pid=fork())<0)
		err_quit("fork error.");
	else if(pid==0)
		abort();
	
	if(wait(&status)!=pid)
		err_quit("wait error.");
	pr_exit(status);
	
	if((pid=fork())<0)
		err_quit("fork error.");
	else if(pid==0)
		status/=0;
	
	if(wait(&status)!=pid)
		err_quit("wait error.");
	pr_exit(status);
	
	if((pid=fork())<0)
		err_quit("fork error.");
	else if(pid==0)
	{
		kill(getpid(),SIGTSTP);
	}
	
	if(wait(&status)!=pid)
		err_quit("wait failed.");
	pr_exit(status);
	exit(0);
}

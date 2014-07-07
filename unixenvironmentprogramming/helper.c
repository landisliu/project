#include"helper.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
void err_quit(char *err)
{
	perror(err);
	exit(1);
}
void sys_log(char * sys)
{
	printf("%s",sys);
	exit(0);
}
void pr_exit(int status)
{
	if(WIFEXITED(status))
	{
		printf("normal termination,exit status= %d\n",WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status))
	{
		printf("abnormal termination,signal number=%d%s\n",WTERMSIG(status),
#ifdef WCOREDUMP
	WCOREDUMP(status)?"(core file generated)":"");
#else
	"");
#endif
	}
	else if(WIFSTOPPED(status))
	{
		printf("child stopped,signal number=%d\n",WSTOPSIG(status));
	}
}

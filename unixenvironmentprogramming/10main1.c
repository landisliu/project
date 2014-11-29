#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void sigfunc(int sig)
{
	printf("signal received:%d\n",sig);
}
int main(int argc,char *argv[])
{
	if(signal(SIGUSR1,sigfunc)==SIG_ERR)
	{
		printf("can't catch SIGUSER1\n");
		exit(1);
	}
	while(1)
		pause();
}

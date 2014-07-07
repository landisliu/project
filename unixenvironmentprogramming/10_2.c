#include"helper.h"
#include<signal.h>
static void sig_usr(int);
int main(int argc,char * argv[])
{
	if(signal(SIGUSR1,sig_usr)==SIG_ERR)
		err_quit("SIGUSR1 error.");
	if(signal(SIGUSR2,sig_usr)==SIG_ERR)
		err_quit("SIGUSR2 error.");
	for(;;)
	pause();
}

static void sig_usr(int signo)
{
	if(signo==SIGUSR1)
	 printf("received SIGUSR1.\n");
	else if(signo==SIGUSR2)
	printf("received SIGUSR2.\n");
	else
		err_quit("error happend.\n");
}

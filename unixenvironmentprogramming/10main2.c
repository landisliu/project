#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pwd.h>
int main(int argc,char * argv[])
{
	
	int uid = getuid();
	#ifdef L_DEBUG
	int euid = geteuid();
	printf("before set euid:%d\n",euid);
	#endif
	if(argc!=2)
		exit(1);
	int pid = atoi(argv[1]);

	/*if(setuid(0)!=0)
	{
		printf("set euid failed.\n");
		exit(1);
	}*/
		
	#ifdef L_DEBUG
	euid = geteuid();
	printf("after set euid:%d\n",euid);
	#endif

	if(kill(pid,SIGUSR1)!=0)
	{
		printf("cannot send signal\n");
		exit(1);
	}
	else
	{
		printf("signal sent\n");
	}
	/*if(setuid(uid)!=0)
	{
		printf("reset uid failed./n");
		exit(1);
	}*/
}

#include"helper.h"
#include<signal.h>
#include<pwd.h>
static void myalarm(int signo)
{
	struct passwd *rootptr;
	printf("in signal handler\n");
	if((rootptr=getpwnam("root"))==NULL)
		printf("get root passwd failed.\n");
	alarm(1);
}
int main(int argc,char * argv[])
{
	setbuf(stdout,NULL);
	struct passwd * ptr;
		signal(SIGALRM,myalarm);
		alarm(1);
	
	for(;;)
	{
		if((ptr=getpwnam("landis"))==NULL)
			printf("get landis passwd failed.\n");
		if(strcmp(ptr->pw_name,"landis")!=0)
			printf("return value corrupted!,pw_name=%s\n",ptr->pw_name);
	}
}

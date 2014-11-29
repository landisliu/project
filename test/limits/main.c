#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc,char * argv[])
{
	int i=0;
	pid_t pid;
	while(i<INT_MAX)
	{
		if((pid=fork())<0)
		{
			printf("fork failed. process count=%d\n",i);
			exit(1);
		}
		else if(pid>0) //parent
		{
			i++;
			printf("%d\n",i);
		}
		else
		{
			pause();
		}
	}
	exit(0);
}

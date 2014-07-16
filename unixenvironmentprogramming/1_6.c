#include"helper.h"
int main(int argc,char * argv[])
{
	pid_t pid = getpid();
	printf("current process pid is:%ld\n",(long)pid);
	exit(0);
}

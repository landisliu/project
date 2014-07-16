#include"helper.h"

#define BUFFSIZE 4096
int main(int argc,char * argv[])
{
	int n;
	char buf[BUFFSIZE];
	
	while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
		if(write(STDOUT_FILENO,buf,n)!=n)
			err_quit("write error.");
	if(n<0)
		err_quit("read error.");
	exit(0);
}

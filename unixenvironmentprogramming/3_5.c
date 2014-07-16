#include"helper.h"
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int n;
	if(argc!=2)
		err_quit("invalid parameter.please input buffer size.");
	int buffersize= 0;	
	buffersize=strtol(argv[1],NULL,10);
	printf("buffersize:%d\n",buffersize);
	char buf[buffersize];
	while((n=read(STDIN_FILENO,buf,buffersize))>0)
		if(write(STDOUT_FILENO,buf,n)!=n)
			err_quit("write failed.");
	if(n<0)
		err_quit("read failed.");
	exit(0);
}

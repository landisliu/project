#include"helper.h"
#include<fcntl.h>
int main(int argc,char *argv[])
{
	char buf1[] ="abcdefghij";
	char buf2[]="ABCDEFGHIJ";
	
	int fd;
	if((fd=creat("file.hole",777))<0)
		err_quit("create file failed.");
	if(write(fd,buf1,10)!=10)
		err_quit("write buf1 failed.");
	if(lseek(fd,16384,SEEK_SET)==-1)
		err_quit("seek failed.");
	if(write(fd,buf2,10)!=10)
		err_quit("write buf2 failed.");
	
	exit(0);
	
}

#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#define BUFSIZE 1000000
char buf[BUFSIZE];
int main(int argc,char * argv[])
{
	int n,send;
	//清空缓存区域
	//bzero(buf,BUFSIZE);
	//读入数据
	if((n = read(STDIN_FILENO,buf,BUFSIZE))>0)
	{
		fprintf(stderr,"read %d bytes\n",n);
	}
	//获取初始值
	int val =fcntl(STDOUT_FILENO,F_GETFL,0);
	//修改标准输出为非阻塞模式
	fcntl(STDOUT_FILENO,F_SETFL,O_NONBLOCK);

	char *ptr = buf;
	while(n>0)
	{
		errno=0;
		send = write(STDOUT_FILENO,ptr,n);
		fprintf(stderr,"write %d bytes,error:%d\n",send,errno);
		if(send>0)
		{	
			ptr+=send;
			n-=send;
		}
	}
	//恢复原来的文件表选项
	fcntl(STDOUT_FILENO,F_SETFL,val);
	exit(0);
}


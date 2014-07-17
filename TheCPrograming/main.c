#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"userlib.h"
#include<time.h>
#include<syslog.h>
int main(int argc,char * argv[])
{
	extern int file1;
	extern int file2;
	extern int file3;
	printf("%d,%d,%d\n",file1,file2,file3);
	return 0;
}


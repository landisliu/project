#include<stdio.h>
#include<stdlib.h>
void calc()
{
	static int num;
	printf("%d\n",num++);
}
void calc2()
{
	register int i = 10;
	printf("%d",i);
}
int main(int argc,char ** argv)
{
	int i;
	//for(i=0;i<atoi(argv[1]);i++)
	//calc();
	calc2();
	exit(EXIT_SUCCESS);
}

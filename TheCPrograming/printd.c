#include<stdio.h>
#include<stdlib.h>
void printd(int n)
{
	if(n<0)
	{
		putchar('-');
		n=-n;
	}
	if(n/10)
		printd(n/10);
	putchar(n%10+'0');
}
int main(int argc,char ** argv)
{
	int num = atoi(argv[1]);
	printd(num);
	exit(EXIT_SUCCESS);
}

#include<stdio.h>
int main(int argc,char *argv[])
{
	char s[] = "\n123\\";
	printf("%d,%d\n",strlen(s),sizeof(s));
	return 0;	
}


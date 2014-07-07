#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void readline(char*);
int main()
{
	int i = rand();
	int array[100];	 
	return 0;
}

void readline(char * chars)
{
	char c = getchar();
	while(c!=EOF)
	{
		*chars=c;
		chars++;
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void readline(char*);
double getd()
{
	return 43.5;
}
int main()
{
	int k = getd();	 
	printf("%d\n",k);
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

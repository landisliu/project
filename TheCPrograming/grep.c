#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define BUFSIZE 1024
char buf[BUFSIZE];
int main(int argc,char * argv[])
{
	char * strarray[BUFSIZE];
	if(argc<2)
	{
		perror("bad input.");
		exit(EXIT_FAILURE);
	}
	char * pattern = argv[1];
	int count=0;
	while(fgets(buf,BUFSIZE,stdin)!=NULL)
	{
		if(strstr(buf,pattern)!=NULL)
		{
			char * pstr = (char *) malloc(strlen(buf)+1);
			strcpy(pstr,buf);
			strarray[count++] = pstr;
		}	
	}
	int i;
	for(i=0;i<count;i++)
	{
		printf("%s",strarray[i]);
	}	
	exit(EXIT_SUCCESS);
}

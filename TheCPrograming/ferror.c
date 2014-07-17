#include<stdio.h>
int main()
{
	FILE * pFile;
	if((pFile=fopen("readme.txt","r"))!=NULL)
	{
	fputc('x',pFile);
	if(ferror(pFile))
	{
		printf("Error Writing to readme.txt.\n");
	}
	fclose(pFile);
	}
	else
	{
		perror("Error opening file");
	}
	return 0;
}

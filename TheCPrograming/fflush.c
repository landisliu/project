#include<stdio.h>
char buffer[80];
int main()
{
	FILE * pFile;
	pFile=fopen("readme.txt","r+");
	if(pFile==NULL)
		perror("Error in open a file.");
	else
	{
		fputs("This is just a test",pFile);
		fflush(pFile);
		fgets(buffer,5,pFile);
		puts(buffer);
		fclose(pFile);
		return 0;
	}
}

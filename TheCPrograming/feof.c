#include<stdio.h>
int main()
{
	FILE * pFile;
	int n=0;
	pFile = fopen("readme.txt","r");
	if(pFile==NULL)
		perror("Error opening file");
	else
	{
		while(fgetc(pFile)!=EOF)
		n++;
		if(feof(pFile))
		{
			puts("End-of-File reached.");
			printf("Total number of bytes read:%d\n",n);
		}
		else
		puts("End-of-File was not reached.");
		fclose(pFile);
	}
	return 0;
}

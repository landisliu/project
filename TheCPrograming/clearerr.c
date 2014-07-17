#include<stdio.h>
int main()
{
	FILE * pFile;
	pFile = fopen("readme.txt","r");
	if(pFile==NULL)
		perror("Error opening file");
	else
	{
		fputc('x',pFile);
		if(ferror(pFile))
		{
			printf("Error writing to readme.txt\n");
			clearerr(pFile);
		}
		fgetc(pFile);
		if(!ferror(pFile))
			printf("No errors reading myfile.txt\n");
		fclose(pFile);
	}
	return 0;
	
}

#include<stdio.h>
int main()
{
	FILE * pFile;
	pFile=fopen("readme.txt","r");
	if(pFile==NULL)perror("Error in open file readme.txt.");
	else
	{
		int c;
		int ret;
		while((c=fgetc(pFile))!=EOF)
			{
				ret = fputc(c,stdout);
				if(ret==EOF)
					perror("error occur when writing.");
			}
		if(ferror(pFile))
			perror("error occur when reading.");
		if(feof(pFile))
			printf("reach the end of readme.txt.\n");
		fclose(pFile);
	}
	return 0;
}

#include<stdio.h>
int main()
{
	FILE * pFile;
	pFile= fopen("readme.txt","a");
	if(pFile==NULL)
	{
		perror("openfile failed.");
		return 1;
	}
	fclose(pFile);
	return 0;
}

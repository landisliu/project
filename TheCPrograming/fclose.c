#include<stdio.h>
int main()
{
	FILE * pFile;
	pFile = fopen("readme.txt","w");
	fprintf(pFile,"fclose example");
	fclose(pFile);
	return 0;
}


#include<stdio.h>
int main()
{
	char array[100];
	char array2[100];
	fgets(array,100,stdin);
	gets(array2);
	
	printf("fgets include newline character.\n");
	printf("fgets:%ld,gets:%ld\n",strlen(array),strlen(array2));
	return 0;
}

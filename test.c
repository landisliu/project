#include<stdio.h>
char buf[]="go with me";
char * buf2 ="go with me";
int main(int argc, char ** argv)
{
	printf("%d\n",sizeof(buf));
	printf("%d\n",sizeof(buf2));
	return 0;
}

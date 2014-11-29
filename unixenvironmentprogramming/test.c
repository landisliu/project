#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define Assert(exp,message) \
{ \
	if(!(exp)) \
	{ \
		printf("Assertion failed. %s\n",#exp); \
		printf("Message:%s\n",message); \
		printf("FileName:%s\n",__FILE__); \
		printf("LineNumber:%d\n",__LINE__); \
	} \
} \

typedef struct Type1
{
	int id;
	char *name;
	struct Type1 *t1;
}eobj;

int main(int argc,char *argv[])
{
	eobj *eos[30];
	printf("struct size:%ld\n",sizeof(eobj));
	printf("arraysize :%ld\n",sizeof(eos));
	printf("array count :%ld\n",sizeof(eos)/sizeof(eobj));
	printf("sizeof long:%ld\n",sizeof(long));
	printf("sizeof short:%ld\n",sizeof(short));
	exit(0);
}

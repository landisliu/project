#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node
{
	char * name;
	int age;
};
static void change(int *a,int *b)
{
	int *c;
	c=a;
	a=b;
	b=c;
}
int main()
{
	int a=10,b=20;
	change(&a,&b);
	printf("%d,%d\n",a,b);
	return 0;
}

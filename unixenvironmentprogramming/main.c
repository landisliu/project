#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/resource.h>
#include<sys/types.h>
void print(char * str)
{
	printf("%s\n",str);
}
typedef void(*pt)(char *str);
typedef void pt2(char * str);
void display(pt pp)
{
	char * str="heeh";
	pp(str);
}
int main(int argc,char * argv[])
{
	//basid use of function
	char * str ="this is the hello world.";
	print(str);
	
	// defind function pointer
	
	pt p1 = print;
	p1(str);

	display(p1);
	//define function
	pt2 * p2 = print;
	p2(str);

	exit(0);
}	


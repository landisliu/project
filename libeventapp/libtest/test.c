#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdarg.h>

struct person
{
	char *name;
	const int age;
};

typedef char *pStr;
const int myfunc(const int);

extern int temp;

int main(int argc,char *argv[])
{
	char string[4] = "abc";
	const char *p1 = string;
	const pStr p2 = string;
	p1++;
	printf("val:%d",temp);
	printf("val2:%d",myfunc(20));

	//p2++; 
	//struct person p1,p2;
	//int * page = &p1.age;
	//*page =100;
	//char *str ="hei";
	//printf("age:%d\n",p1.age);

	//p1.name= malloc(100);
	//p2.name = malloc(100);
	//strcpy(p1.name,str);
	//strcpy(p2.name,str);
	
	//printf("p1.age:%d,p2.age%d,p1.name:%s,p2.name:%s\n",p1.age,p2.age,p1.name,p2.name);	
	//free((void *)p1.name);
	//free((void *)p2.name);
	return 0;	
}
const int myfunc(const int abc)
{
	int d = abc;
	d = 9;
	return d;
}
void display(int a,...)
{
}

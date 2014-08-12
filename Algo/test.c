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
static struct node * alloc_node()
{
	struct node * pn1;
	return (struct node *)malloc(sizeof(pn1)+sizeof(int));
}
static void free_node(struct node * p)
{
	free(p);	
}
void setval(struct node * p)
{
	char buf[1024];
	fgets(buf,1024,stdin);
	p->name =buf;
	p->age=10;
}
int main()
{
	struct node n1;
	setval(&n1);
	printf("%s,%d\n",n1.name,n1.age);
	return 0;
}

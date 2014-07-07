#include"calc.h"
static int sp = 0;
static double stack[BUFSIZE];
void push(double ch)
{
	if(sp >= BUFSIZE)
	{
		printf("stack is full.nothing can be pushed\n");
		exit(1);
	}

	stack[sp++] = ch;
}
void trypop(void)
{
	if(sp<=0)
	{
		printf("stack is empty.");
	}
	int i = sp-1;
	printf("stack top is:%g",stack[i]);
}

double copypop(void)
{
	if(sp<=0)
	{
		printf("stack is empty.");
	}
	int i = sp-1;
	return stack[i];
}

void clear(void)
{
	sp = 0;
}

double pop(void)
{
	if(sp<=0)
	{
		printf("stack is empty.nothing can be popped\n");
		exit(1);
	}
	return stack[--sp];
}
void exchange(void)
{
	if(sp<2)
	{
		printf("on more elements for exchange.\n");
		return;
	}
	double first = pop();
	double second = pop();
	push(first);
	push(second);
}

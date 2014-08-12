#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define STACKSIZE 1024
int array[STACKSIZE];
int p = 0;

void push(int key)
{
	*(array+p)=key;
	p++;
}
int pop()
{
	p--;
	return *(array+p);
}


int main(int argc,char * argv[])
{

	int c,p1,p2;
	int i =0;
	int val=0;
	int flag =1;
	int sig=1;
	int nextc;
	while((c=getchar())!=EOF)
	{
		if(isdigit(c))
		{
			if(flag==1)
				val=val*10+c-'0';
			else
			{
				val =c-'0';
				flag=1;
			}
			continue;
		}
		else
		{
			if(1==flag)
			{
				push(sig*val);
				flag =0;
			}

			if(c=='-')
			{
				nextc = getchar();
				ungetc(nextc,stdin);
				if(isdigit(nextc))
				{
				  sig=-1;
				  continue;
				}
			}

			if(isblank(c))
			   continue;
		}
		
		switch(c)
		{
			case '+':push(pop()+pop());break;
			case '-':
					p1 = pop();
					p2 = pop();
					push(p2-p1);
					break;
			case '*':push(pop()*pop());break;
			case '/':
					p1 = pop();
					p2 = pop();
					push(p2/p1);
				break;
			case '\n':printf("%d\n",pop());break;
		}
	}
	return 0;
}

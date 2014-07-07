#include"calc.h"
int main(int argc,char ** argv)
{
	int type;
	double op2;
	char s[MAXOP];
	while((type=getop(s))!=EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop()+pop());
				break;
			case '*':
				push(pop()*pop());
				break;
			case '-':
				op2 = pop();
				push(pop()-op2);
				break;
			case '/':
				op2 = pop();
				if(op2==0)
				{
				printf("divide zero exception.\n");
				exit(1);
				}
				else
				{
					push(pop()/op2);
				}
				break;
			case '%':
				op2 = pop();
				push((int)pop()%(int)op2);
				break;
			case '\n':
				printf("\t%.8g\n",pop());
				break;
			case 's':push(sin(pop()));break;
			case 'e':push(exp(pop()));break;
			case 'p':
				op2 = pop();
				push(pow(pop(),op2));
				break;
			default:
				printf("error:unknown command %s\n",s);
				break;
		}
	}
	exit(0);
}

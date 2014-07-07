#include"calc.h"
static char buf[BUFSIZE];
static int index_buf = 0;
int getch(void)
{
	return (index_buf>0)?buf[--index_buf]:getchar();
}

void ungetch(int ch)
{
	if(index_buf>=BUFSIZE)
	{
		printf("cache is full.\n");
		exit(1);
	}
	
	buf[index_buf++] = ch;
}

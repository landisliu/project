#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
extern void start_time();
extern void end_time();
void tobs(int * tarray,void *source)
{
	switch(typeof(*source))
	{
		case int: printf("int\n");break;
		case double:printf("double\n");break;
	}
}
int main()
{
	int l = 1<<31;
	printf("%d\n",l);
	int i=0;
	int k=1;
	char buf[sizeof(int)]
	while(i<sizeof(int))
	{
		printf("%d,%d\n",i,l&k);
		l=l>>1;
		i++;
	}
	tobs(NULL,&k);
	printf("\n");
	return 0;
}

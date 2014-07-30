#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define ARRAYSIZE 2024000
static void exchange(int * array,int index1,int index2)
{
	int temp = *(array+index1);
	*(array+index1) = *(array+index2);
	*(array+index2) = temp;
}
static inline void display(int * array)
{
	int i;
	for(i=0;i<ARRAYSIZE;i++)
		printf("%d\n",*(array+i));
}

static void init(int * array)
{
	int i;
	srand(ARRAYSIZE);
	for(i=0;i<ARRAYSIZE;i++)
	{
		*(array+i) = rand()%ARRAYSIZE+1;
	}
}

static void statistics(char * algo,clock_t start,clock_t end,int comTimes,int exchangeTimes)
{
	printf("%s ticks slapsed:%ld,time slapsed:%lf,compare times:%d,exchange times:%d\n",algo,end-start,((float)(end-start))/CLOCKS_PER_SEC,comTimes,exchangeTimes);
}

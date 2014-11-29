#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 11
#define Error 1
typedef struct AQueue
{
	int aq[MAXSIZE];
	int front,end;
}Queue,*QueuePtr;
void Enque(QueuePtr q,int em)
{
	if((q->end-q->front+MAXSIZE)%MAXSIZE==MAXSIZE-1)
		exit(Error);
	q->aq[q->end] = em;
	q->end = (q->end +1)%MAXSIZE;
}
int Deque(QueuePtr q)
{
	if(q->end ==q->front)
	{
		exit(Error);
	}
	int ret = q->aq[q->front];
	q->front = (q->front+1)%MAXSIZE;
	return ret;
}
int InitQueue(QueuePtr q)
{
	q->front=q->end=0;
}

int QueueLength(QueuePtr q)
{
	return (q->end-q->front+MAXSIZE)%MAXSIZE;
}

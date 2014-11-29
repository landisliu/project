#include<stdio.h>
#include<stdlib.h>

#define Error 1

//typedef int int

typedef struct MyNode
{
	int data;
	struct MyNode *next;	
}LNode,*NodePtr;

typedef struct
{
	NodePtr front;
	NodePtr end;
}LinkQueue;


void Enque(LinkQueue * LQ,int em)
{
	NodePtr s = (NodePtr)malloc(sizeof(LNode));
	if(!s)
		exit(Error);
	s->data = em;
	s->next = NULL;
	
	LQ->end->next = s;
	LQ->end =s;
}

int Deque(LinkQueue * LQ)
{
	if(LQ->front==LQ->end)
		exit(Error);
	NodePtr p =LQ->front->next;
	LQ->front->next = p->next;
	
	if(p==LQ->end)
		LQ->end=LQ->front;
	int em = p->data;
	free((void *)p);
	return em;	
}

void InitQue(LinkQueue * LQ)
{
	NodePtr head = (NodePtr)malloc(sizeof(LNode));
	head->next =NULL;
	LQ->front=LQ->end=head;
}

void DestroyQue(LinkQueue *LQ)
{
	NodePtr p = LQ->front->next;
	while(p)
	{
		NodePtr q=p;
		p=p->next;
		free(q);
	}
	free(LQ->front);
}

int main(int argc,char * argv[])
{
	LinkQueue LQ;
	InitQue(&LQ);
	int i;

	for(i=0;i<100;i++)
	{
		Enque(&LQ,(int)i);
	}

	for(i=0;i<100;i++)
	{
		printf("%d\n",(int)Deque(&LQ));
	}
	DestroyQue(&LQ);
	return 0;
}

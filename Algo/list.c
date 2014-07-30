#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BUFSIZE 1024

char buf[BUFSIZE];

struct list_node
{
	struct person_node * node;
        struct list_node * prev;
        struct list_node * next;
};

struct person_node
{
        char * name;
        char * desc;
        int age;
};

static struct list_node * init()
{
	struct list_node * head =(struct list_node *)malloc(3*sizeof(head));
	head->next = head;
	head->prev = head;
	head->node = NULL;
	return head;
}

static void add_node(struct list_node *head)
{
	struct person_node *pnode=(struct person_node *)malloc(2*sizeof(head)+sizeof(int));
	printf("please input name:\n");
	fgets(buf,BUFSIZE,stdin);
	buf[strlen(buf)-1]=0;
	pnode->name = (char *)malloc(strlen(buf)+1);
	strcpy(pnode->name,buf);

	printf("please input desc:\n");
	fgets(buf,BUFSIZE,stdin);
	buf[strlen(buf)-1]=0;
	pnode->desc = (char *)malloc(strlen(buf)+1);
	strcpy(pnode->desc,buf);

	printf("please input age:\n");
	fgets(buf,BUFSIZE,stdin);
	pnode->age = atoi(buf);
	

	struct list_node *lnode =(struct list_node*) malloc(3*sizeof(head));
	lnode->node = pnode;
	
	lnode->next=head->next;
	head->next->prev =lnode;
	head->next=lnode;
	lnode->prev = head;
	
}

static void release_list_node(struct list_node * lnode)
{
	free(lnode);
}

static void release_person_node(struct person_node *pnode)
{
	free(pnode->name);
	free(pnode->desc);
	free(pnode);
}
static void destroy_list(struct list_node *head)
{
	free(head);
}

static void remove_node(struct list_node *head,char *name)
{
	struct list_node *p = head;
	do	
	{
		if(p->node!=NULL)
		{
			if(strcmp(p->node->name,name)==0)
			{

				p->prev->next=p->next;
				p->next->prev=p->prev;

				release_person_node(p->node);
				release_list_node(p);

				printf("remove success...\n");
				return;
			}	
		}
		p=p->next;
	}while(p!=head);
	printf("remove failed, not find....");
}

static long count(struct list_node *head)
{
	struct list_node *p = head;
	long c=0;
	do
	{
		if(p->node!=NULL)
		{
			c++;
		}
		p=p->next;
	}while(p!=head);
	return c;
}


static void traverse(struct list_node *head)
{
	struct list_node *p = head;
	do
	{
		if(p->node!=NULL)
		{
			printf("%s,%s,%d\n",p->node->name,p->node->desc,p->node->age);
		}
		p=p->next;
	}while(p!=head);
}

static void reverse_traverse(struct list_node * head)
{
	struct list_node *p = head;
	do
	{
		if(p->node!=NULL)
		{
			printf("%s,%s,%d\n",p->node->name,p->node->desc,p->node->age);
		}
		p=p->prev;
	}while(p!=head);
}

static struct list_node * search_node(struct list_node * head,char * name)
{
	struct list_node *p = head;
	do
	{
		if(p->node!=NULL)
		{
			if(strcmp(p->node->name,name)==0)
			{
				return p;
			}
		}
		p=p->next;
	}while(p!=head);
	return NULL;
}

int main()
{
	struct list_node * head = init();
	int i;	
	for(i=0;i<5;i++)
	{
		add_node(head);
		printf("current count:%d\n",count(head));
	}
	printf("input a name to remove\n");
	fgets(buf,BUFSIZE,stdin);

	buf[strlen(buf)-1] =0;
	printf("firstly we will search this item");
	if(search_node(head,buf)!=NULL)
	{
		remove_node(head,buf);
	}			

	printf("current count:%d\n",count(head));

	printf("traverse in order desc\n");
	traverse(head);
	printf("traverse in order asc\n");
	reverse_traverse(head);
        return 0;
}

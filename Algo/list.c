#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct list_node
{
        struct list_node * prev;
        struct list_node * next;
};

struct person_node
{
        char * name;
        char * desc;
        int age;
        struct list_node * node;
};
int main()
{

        struct list_node * node;
        node->prev=node;
        node->next=node;
        struct person_node pnode;
        pnode.name="landis";
        pnode.desc="I am a good man";
        pnode.age = 20;
        pnode.node= node;

        printf("%s,%s,%d",pnode.name,pnode.desc,pnode.age);
        return 0;
}

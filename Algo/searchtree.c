#include"helper.h"
struct tree_node
{
	int key;
	struct tree_node *parent;
	struct tree_node *left;
	struct tree_node *right;
};

static void insert_tn(struct tree_node *root,int key)
{
	struct tree_node * node =(struct tree_node*)malloc(3*sizeof(root)+sizeof(int));
	node->left=NULL;
	node->right=NULL;
	node->key = key;

	struct tree_node *p =root;

	while(p!=NULL)
	{
		if(key<=p->key)
		{
			if(p->left!=NULL)
				p=p->left;
			else
			{
				node->parent = p;
				p->left=node;
				break;
			}
		}
		if(key>=p->key)
		{
			if(p->right!=NULL)
				p=p->right;
			else
			{
				node->parent=p;
				p->right=node;
				break;
			}
		}
	}
}

static struct tree_node* init_troot(int key)
{
	struct tree_node * root = (struct tree_node*)malloc(3*sizeof(root)+sizeof(int));
	root->key = key;
	root->parent =NULL;
	root->left=NULL;
	root->right=NULL;
	return root;
}

static void LDR(struct tree_node * root)
{
	if(root->left!=NULL)
		LDR(root->left);
	printf("%d\n",root->key);
	if(root->right!=NULL)
		LDR(root->right);
}

static void release(struct tree_node *root)
{
	if(root->left!=NULL)
		release(root->left);
	if(root->right!=NULL)
		release(root->right);
	free(root);
}
int main()
{
	struct tree_node *root=NULL;
	srand(ARRAYSIZE);
	int i;
	int key;
	clock_t t1,t2;
	t1 = clock();
	for(i=0;i<ARRAYSIZE;i++)
	{
		key = rand()%ARRAYSIZE+1;
		if(root==NULL)
		{
			root = init_troot(key);
		}
		else
		{
			insert_tn(root,key);
		}
	}
	t2 = clock();
	statistics("searchtree",t1,t2,0,0);
	release(root);
	return 0;
}

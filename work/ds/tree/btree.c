#include<stdio.h>
#include<stdlib.h>
#define NAMESIZE 25

struct data_st{
	int id;
	char name[NAMESIZE];
	int score;
	};
struct node_st{
	struct data_st data;
	struct node_st* l;
	struct node_st *r;
	};
struct node_st* tree=NULL;
void print_s(struct data_st *p)
{
	printf("%d %s %d\n",p->id,p->name,p->score);	
}
int tree_insert(struct node_st** root,struct data_st *data)
{
	struct node_st *node;
	if(*root==NULL)
	{
		node=malloc(sizeof (*node));	
		if(node==NULL)
		{
			return -1;	
		}
		node->data=*data;
		node->l=NULL;
		node->r=NULL;
		*root=node;
		return 0;
	}
	if(data->id<=(*root)->data.id)
	{
		return tree_insert(&(*root)->l,data);	
	}
	else
	{
		return tree_insert(&(*root)->r,data);	
	}
}
struct data_st *tree_find(struct node_st *root,int id)
{
	if(root==NULL)
	{
		return NULL;	
	}
	if(id==root->data.id)
	{
		return &root->data;
	}
	if(id<root->data.id)
	{
		return tree_find(root->l,id);	
	}
	else
	{
		return tree_find(root->r,id);	
	}
}
void draw_(struct node_st* p,int lev)
{
	int i;
	if(p==NULL)
	{
		return ;	
	}
	draw_(p->r,lev+1);
	for(i=0;i<lev;i++)
	{
		printf("	");	
	}
	print_s(&p->data);
	draw_(p->l,lev+1);
}
void draw(struct node_st *p)
{
	draw_(p,0);
	//getchar();
}
int get_num(struct node_st *root)
{
	if(root==NULL)
	{
		return 0;	
	}
	return get_num(root->l)+1+get_num(root->r);
}
struct node_st *find_min(struct node_st *root)
{
	if(root->l==NULL)
		return root;
	return find_min(root->l);
}
struct node_st *find_max(struct node_st *root)
{
	if(root->r==NULL)
		return root;
	return find_max(root->r);
}
void turn_left(struct node_st **root)
{
	struct node_st *cur =*root;
	*root=cur->r;
	cur->r=NULL;
	find_min(*root)->l=cur;
	//draw(tree);
	return ;
}  
void turn_right(struct node_st **root)
{
	struct node_st* cur =*root;
	*root=cur->l;
	cur->l=NULL;
	find_max(*root)->r=cur;
	return ;
}
void balance(struct node_st** root)
{
	int sub;
	if(*root==NULL)
	{
		return ;	
	}
	while(1)
	{
		sub=get_num((*root)->l)-get_num((*root)->r);
		if(sub>=-1&&sub<=1)
			break;
		if(sub<-1)
		{
			turn_left(root);	
		}
		else
		{
			turn_right(root);	
		}
	}
	balance(&(*root)->l);
	balance(&(*root)->r);
}
void travel(struct node_st *root)
{
	if(root==NULL)
	{
		return ;	
	}
	print_s(&root->data);
	travel(root->l);	
	travel(root->r);
}
int main(void)
{
	int arr[]={1,2,3,7,6,5,9,8,4};
	int i;
	struct data_st tmp,*datap;
	
	for(i=0;i<(sizeof(arr)/sizeof(*arr));i++)
	{
		tmp.id=arr[i];	
		snprintf(tmp.name,NAMESIZE,"std%d",arr[i]);
		tmp.score=100-arr[i];
		tree_insert(&tree,&tmp);
	}
	draw(tree);
	balance(&tree);
	travel(tree);
	//draw(tree);
#if 0	
	int id=8;
	datap=tree_find (tree,id);
	if(datap==NULL)
	{
		printf("not find\n");	
	}
	print_s(datap);
#endif
	return 0;	
}

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct node_st
{
	char data;
	struct node_st *l,*r;
};

static struct node_st *tree = NULL;

int insert(struct node_st **root,int data)
{
	struct node_st *node;

	if(*root == NULL)
	{
		node = malloc(sizeof(*node));
		if(node == NULL)
			return -1;
		node->data = data;
		node->l = NULL;
		node->r = NULL;
		*root = node;
		return 0;
	}

	if(data <= (*root)->data)
		return insert(&(*root)->l,data);
	return insert(&(*root)->r,data);
}


static void draw_(struct node_st *root,int level)
{
	int i;

	if(root == NULL)
		return ;

	draw_(root->r,level+1);
	
	for(i = 0 ; i < level; i++)
		printf("    ");
	printf("%c\n",root->data);
	
	draw_(root->l,level+1);
}

void draw(struct node_st *root)
{
	draw_(root,0);	
}
void save(struct node_st *root,FILE *fp)
{
	fputc('(',fp);
	if(NULL==root)
	{

		fputc(')',fp);
		return ;
	}
	fputc(root->data,fp);
	save(root->l,fp);
	save(root->r,fp);
	fputc(')',fp);
}
int main()
{
	FILE *fp=NULL;
	char arr[] = "ceadb";
	int i;
	char res[]={};
	fp=fopen("tmp","w");
	if(NULL==fp)
	{
		printf("fopen()failed\n");
		return -1;
	}
	for(i = 0 ; i < sizeof(arr)-1 ; i++)	
	{
		insert(&tree,arr[i]);
	}

	draw(tree);
	fputc('(',fp);
	save(tree,fp);
	fputc(')',fp);
	printf("%s\n",res);
	fclose(fp);
	exit(0);
}



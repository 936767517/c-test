#include <stdio.h>
#include <stdlib.h>

struct node_st
{
	char data;
	struct node_st *l,*r;
};

static struct node_st *tree = NULL;

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

struct node_st *load_(FILE *fp)
{
	struct node_st *root;
	int ch;

	ch = fgetc(fp);
	if(ch != '(')
	{
		fprintf(stderr,"read error.\n");
		return NULL;
	}

	ch = fgetc(fp);
	if(ch == ')')
		return NULL;

	root = malloc(sizeof(*root));	
	root->data = ch;
	root->l = load_(fp);
	root->r = load_(fp);

	fgetc(fp);		// must be ')'

	return root;
}

struct node_st *load(const char *path)
{
	FILE *fp;
	struct node_st *root;	

	fp = fopen(path,"r");
	if(fp == NULL)
	{
		perror("fopen()");
		return NULL;
	}
	root = load_(fp);
	
	fclose(fp);
	return root;
}

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage....\n");
		exit(1);
	}

	tree = load(argv[1]);
	draw(tree);

	exit(0);
}



#include<stdio.h>
#include<stdlib.h>
struct node_st
{
	char data;
	struct node_st *l,*r;
	
};
struct node_st *load(FILE *fp)
{
	int  ch;
	struct node_st *root;
	ch=fgetc(fp);
	if(ch!='(')
	{
		return NULL;	
	}
	ch=fgetc(fp);
	if(ch==')')
	{
		return NULL;	
	}
	root=malloc(sizeof(*root));
	root->data=ch;
	root->l=load(fp);
	root->r=load(fp);
	fgetc(fp);
	return root;
}
int main(int argc,char **argv)
{
	if(argc<2)
	{
		printf("....src\n");
		return -1;
	}
	int i=0;
	FILE *fp=NULL;
	char buff[100]={};
	char ch;
	fp=fopen(argv[1],"r");
	if(NULL==fp)
	{
		return -1;	
	}
	load(fp);
	fclose(fp);
	return 0;	
}

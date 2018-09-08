#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHSIZE 26
#define KEYSIZE 128
struct node_st{
	int num;	
	struct node_st* ch[CHSIZE];
	
};
int get_word (FILE* fp,char *key)
{
	char ch;
	int i;
	int j;
	ch=fgetc(fp);
	for(i=0;ch!=EOF&&i<KEYSIZE-1;i++)
	{
		if(!(ch>='a'&&ch<='z'))
		{
			key[i]='\0';
			return 0;
		}
		key[i]=ch;	
		ch=fgetc(fp);
	/*	printf("i=%d",i);
		for(j=0;j<10;j++)
		{
			printf("[%c]",key[j]);
			if(key[j]=='\0')
			{
				break;	
			}
		}*/
	}
	key[i]='\0';
	return -1;
}
struct node_st* newnode(void)
{
	int i;
	struct node_st* tree=(struct node_st*)malloc(sizeof(*tree));
	if(tree==NULL)
	{
		return NULL;	
	}
	tree->num=0;
	for(i=0;i<CHSIZE;i++)
	{
		tree->ch[i]=NULL;	
	}
	return tree;
}
int insert (struct node_st**root,char *key)
{
	
	if(*root==NULL)
	{
		*root=newnode();
		if(*root==NULL)
		{
			return -1;	
		}
	}
	if(*key=='\0')
	{
		(*root)->num++;
	//	printf("num=%d\n",(*root)->num);
		return 0;
	}
	return insert((*root)->ch+*key-'a',key+1);
}
int find(struct node_st* root,char *key)
{
	if(root==NULL)
	{
		return 0;
	}
	if(*key=='\0')
		{
			//printf("key=%d\n",root->num);
			return root->num;
		}
		else
		{
			return find(root->ch[*key-'a'],key+1);
		}
}
int main(int argc,char**argv)
{
	if(argc<2)
	{
		printf("Usage...\n");
		return -1;
	}
	char key[KEYSIZE]={};
	struct node_st *tree =NULL;
	FILE *fp;
	int res;
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("fopen error\n");
		return -2;
	}
	while(1)
	{
		res=get_word(fp,key);
		if (res==-1)
		{
			break;	
		}
		insert(&tree,key);
	}
	char tmp[KEYSIZE]="bi";
	//char tmp[KEYSIZE]="a";
	int retp=find(tree,&tmp[0]);
	if(retp==0)
	{
		printf("not find\n");	
	}
	else
	{
		printf("%s=[%d]\n",tmp,retp);
	}
	fclose(fp);
	return 0;	
}

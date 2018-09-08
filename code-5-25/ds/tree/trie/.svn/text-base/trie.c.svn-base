#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESCSIZE		128
#define KEYSIZE			128
#define BUFSIZE			128
#define CHR_NR			26

struct node_st
{
	char *desc;
	struct node_st *ch[CHR_NR];
};

int get_word(FILE *fp,char *key,char *desc)
{
	int i;
	char buf[BUFSIZE];
	char *s;
	char *retp;
	
	retp = fgets(buf,BUFSIZE,fp);
	if(retp == NULL)
		return -1;
	
	for(s = buf,i = 0 ; i < KEYSIZE-1 && *s != ':'; i++,s++)
		key[i] = *s;
	key[i] = '\0';
	
	s++;	

	for(i = 0 ; i < DESCSIZE-1 && *s != '\n'; i++,s++)	
		desc[i] = *s;
	desc[i] = '\0';

	return 0;
}

struct node_st *newnode(void)
{
	int i;
	struct node_st *node;

	node = malloc(sizeof(*node));

	if(node == NULL)
		return NULL;
	
	node->desc = NULL;
	
	for(i = 0 ; i < CHR_NR; i++)
		node->ch[i] = NULL;

	return node;
}

int insert(struct node_st **root,char *key,char *desc)
{
	
	if(*root == NULL)
	{
		*root = newnode();
		if(*root == NULL)
			return -1;
	}

	if(*key == '\0')
	{
		(*root)->desc = malloc(strlen(desc)+1);
		strcpy((*root)->desc,desc);
		return 0;
	}
	
	return insert((*root)->ch+*key-'a',key+1,desc);
}

char *find(struct node_st *root,char *key)
{
	if(root == NULL)
		return NULL;
	if(*key == '\0')
		return root->desc;
	return find(root->ch[*key-'a'],key+1);
}

int main(int argc,char **argv)
{
	FILE *fp;
	char key[KEYSIZE],desc[DESCSIZE];	
	struct node_st *tree = NULL;
	char *retp;
	int ret;

	if(argc < 2)
	{
		fprintf(stderr,"Usage....\n");
		exit(1);
	}	

	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	while(1)
	{
		ret = get_word(fp,key,desc);
		if(ret == -1)
			break;
		insert(&tree,key,desc);
	}

	char *tmp = "donk"; //"ant";
	retp = find(tree,tmp);
	if(retp == NULL )
		printf("Can't find!\n");
	else
		puts(retp);

	fclose(fp);

	exit(0);
}



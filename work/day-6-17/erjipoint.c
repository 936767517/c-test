#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void get_mem(char **p,int size)
{
	*p=(char*)realloc(*p,size);
	if(NULL==*p)
	{
		return; 
	}
}
void dispose(char **q,int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		free(q[i]);	
	}
	free(q);
}
int main(void)
{
	 char ch;
	 char *p=NULL;
	 char **q=NULL;
	int i;
	int num=0;
	int count=0;
	while(1)
	{
		scanf("%c",&ch);
		if(ch == '\n')
		{
			break;	
		}
		if(ch!=' ')
		{
			count++;
			p=realloc(p,(count+1)*sizeof(char));
			if(p==NULL)
			{
				return -1;	
			}
			p[count-1]=ch;
			p[count]='\0';
			//puts(p);
			//printf("%d = %p\n", num, p);
		}
		else
		{
			p[count]='\0';
			if(0==strcmp(p,"quit"))
			{
				break;	
			}
			num++;
			q=realloc(q,sizeof(char*)*num);
			if(q==NULL)
			{
				return -2;	
			}
			q[num-1]=p;
			p=NULL;
			count=0;
		}
	}
	for(i=0;i<num;i++)
	{
		printf("%s\n",q[i]);	
	}
	dispose(q,num);
	
	return 0;	
}

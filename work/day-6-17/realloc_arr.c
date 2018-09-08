#include <stdio.h>
#include<stdlib.h>
#include<string.h>
	void free_(char ** q,int size)
	{
		int i;
	for(i=0;i<size;i++)
	{
		free(q[i]);	
	}
	free(q);
	}
int main(void)
{
	char **q=NULL;
	char s[100]={};
	int count=0;
	int i;
	while(1)
	{
		scanf("%s",s);
		if(0==strcmp(s,"quit"))
		{
			break;	
		}
		count++;
		q=(char**)realloc(q,count*sizeof(char*));
		if(NULL==q)
		{
			free_(q,count-1);
			return -1;	
		}
		q[count-1]=(char *)realloc(q[count-1],strlen(s)+1);
		if(NULL==q[count-1])
		{
			free_(q,count-1);
			return -2;	
		}
		strcpy(q[count-1],s);
	}
	for(i=0;i<count;i++)
	{
		printf("%s ",q[i]);	
	}
	printf("\n");
	free_(q,count);
	return 0;	
}

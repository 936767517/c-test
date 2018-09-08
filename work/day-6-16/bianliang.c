#include<stdio.h>
#include<stdlib.h>
#define size 100
int main(void)
{
	int i;
	int *p=NULL;
	int num;
	int count=0;
	int n=0;
	while(1)
	{
		scanf("%d",&num);
		if(0==num)
		{
			break;	
		}
		count++;
		
		if(count*sizeof(int)>n*size)
		{
			p=(int*)realloc(p,size*(++n));
			if(NULL==p)
			{
				return -1;	
			}
		}
		
	
			p[count-1]=num;
		
	}
	p=realloc(p,count*sizeof(int));
	if(NULL==p)
	{
		return -2;	
	}
	for(i=0;i<count;i++)
	{
		printf("%d ",p[i]);	
	}
	printf("\n");
	free(p);
	return 0;
}

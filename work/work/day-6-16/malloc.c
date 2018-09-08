#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int *p=NULL;
	int i;
	int j;
	int tmp=0;
	char enable;
	while(1)
	{
		scanf("%d",&tmp);
		scanf("%c",&enable);
		p=realloc(p,4*(i+1));
		if(p==NULL)
		{
			printf("realloc error");	
			return -1;
		}
		else
		{
			*(p+i)=tmp;
			i++;
			if(enable=='\n')
			{
				break;	
			}
			else
			{
				continue;
			}
		}
	}
		for(j=0;j<i;j++)
		{
			printf("%d ",*(p+j));
		}
		printf("\n");
	free(p);
	return 0;	
}

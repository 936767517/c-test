#include<stdio.h>
int main(void)
{
	int m;
	int i,j;
	scanf("%d",&m);
	int a=1;
	for(i=0;i<m;i++)
	{
		a=1+2*i;
	}
	printf("a=%d\n",a);
	for(i=0;i<m;i++)
	{
		for(j=0;j<=a;j++)
		{
			if(j>=(((a/2))-i)&&j<=(((a/2))+i))
			{
				printf("*");
			}
			else{
			printf(" ");
			}
		}
		printf("\n");

	}

	return 0;
}

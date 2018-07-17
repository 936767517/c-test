#include<stdio.h>
int main(void)
{
	int a[5][5]={};
	int i,j;
	int n=1;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
		a[i][j]=n++;	
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<=i;j++)
		{
			printf("%2d ",a[i][j]);	
		}
		printf("\n");
	}
	return 0;	
}

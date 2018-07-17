#include<stdio.h>
void get_(int b[][3],int x)
{
	int i,j;
	int n=2;
	for(i=0;i<x;i++)
	{
		for(j=0;j<3;j++)
		{
			b[i][j]=n;
			n+=2;
		}
	}
}
void print_(int b[][3],int x)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<x;j++)
		{
			printf("%d ",b[j][i]);	
		}
		printf("\n");
	}
}
int main(void)
{
	int b[2][3]={};
	get_(b,2);
	print_(b,2);
	return 0;	
}

#include<stdio.h>
void change(int a[][3],int x,int b[][2],int y)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			b[j][i]=a[i][j];
		}
	}
}
void print(int b[][2],int x)
{
	int i,j;
	for(i=0;i<x;i++)
		{
			for(j=0;j<2;j++)
			{
				printf("%d ",b[i][j]);	
			}
			printf("\n");
		}
}
int main(void)
{
	int a[2][3]={{1,2,3},{4,5,6}};
	int b[3][2]={};

	change(a,2,b,3);
	print(b,3);

	return 0;	
}

#include <stdio.h>
void init_arr(int a[],int x)
{
	int i;
	for	(i=0;i<x;i++)
	{
		scanf("%d",&a[i]);	
	}
	
}
void get_div(int a[],int x,int b[],int y)
{
	int i;
	for(i=0;i<y;i++)
	{
		b[i]=a[i+1]/a[i];
	}
}
void print(int b[],int y)
{
	int i;
	for(i=0;i<y;i++)
	{
		printf("%d ",b[i]);
		if((i+1)%3==0)
		{
			printf("\n");	
		}
	}
}
int main(void)
{
	int a[10];
	int b[10];

	init_arr(a,10);
	get_div(a,10,b,9);
	print(b,9);

	return 0;
}

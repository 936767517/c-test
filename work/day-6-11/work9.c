#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void array_init(int arr[][9],int m,int n)
{
	int i,j;
	int num;
	for(i=0;i<m;i++)
	{
		for(j=0,num=i+1;j<n;j++,num++)
		{
			arr[i][j]=num;
			if(num==m)
			{
				num=0;	
			}
		}
	}
}
void array_print(int arr[][9],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",arr[i][j]);	
		}
		printf("\n");
	}
}
int main(void)
{
	srand(time(NULL));
	int arr[9][9]={};
	int m=rand()%8+2;
	printf("m=%d\n",m);
	array_init(arr,m,m);
	array_print(arr,m,m);

	return 0;
}

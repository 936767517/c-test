#include<stdio.h>
void array_print(int arr[][3],int m,int n)
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
void func(int arr[][3])
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(j>=i)
			{
				arr[i][j]=0;	
			}
			
		}
	}
	
}
int main(void)
{	
	int arr[3][3];
	int i,j;
	int num=1;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			arr[i][j]=num++;	
		}
	}
	array_print(arr,3,3);
	func(arr);
	array_print(arr,3,3);
	return 0;	
}

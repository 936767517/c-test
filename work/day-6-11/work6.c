#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void array_init(int arr[][4],int m,int n)
{
	srand(time(NULL));
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			arr[i][j]=rand()%100;	
		}
		
	}
	
}
void array_print(int arr[][4],int m,int n)
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
void Max(int arr[][4],int m,int n)
{
	int i,j;
	int max=arr[0][0];
	int a,b;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(arr[i][j]>=max)
			{
				max=arr[i][j];
				a=i;
				b=j;
			}
		}
			
	}
	for(i=0;i<m;i++)
	{
		for(i=0;i<n;i++)
		{
			if(arr[i][j]==max)
			{
					
				printf("max=%d m=%d n=%d\n",max,i,j);
			}
		}
	}
				printf("max=%d m=%d n=%d\n",max,a,b);
}
int main(void)
{
	int arr[3][4];
	array_init(arr,3,4);
	array_print(arr,3,4);
	Max(arr,3,4);
	return 0;	
}

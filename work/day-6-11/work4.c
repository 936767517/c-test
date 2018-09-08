#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10
void array_init(int *arr,int n)
{
	int i;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		arr[i]=rand()%100;
	}
}

int main(void)
{
	int arr[N]={};
	int num;
	int i,j;
	int m;
	scanf("%d",&num);
	array_init(arr,10);
	for(i=0;i<N;i++)
	{
		printf("%d ",arr[i]);	
	}
	printf("\n");
	for(i=0;i<num%N;i++)
	{
			m=arr[0];
		for(j=0;j<N-1;j++)
		{
			arr[j]=arr[j+1];
		}
		arr[N-1]=m;
	}

	for(i=0;i<10;i++)
	{
		printf("%d ",arr[i]);	
	}
	printf("\n");
	return 0;	
}

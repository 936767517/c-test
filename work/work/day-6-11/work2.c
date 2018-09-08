#include<stdio.h>
#include"array.h"
#include<time.h>
#include<stdlib.h>
#define N 20
int main(void)
{
	srand(time(NULL));
	int arr[N]={};
	int i;
	int m=0;
	int n=0;
	array_init(arr,rand()%10+10);
	for(i=0;i<N;i++)
	{
		printf("%d ",arr[i]);
		if(arr[i]>0&&arr[i]%2==1)
		{
			m++;	
		}
		else if(arr[i]<0)
		{
			n++;	
		}

	}
	printf("\n");
	
	printf("m=%d n=%d\n",m,n);
}

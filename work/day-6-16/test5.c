#include<stdio.h>
void fun(int *arr,int m,int n)
{
	int *head=arr+m;
	int *tail=arr+m+n;
	for(;head<tail;head++,tail--)
	{
		int tmp;
		tmp=*head;
		*head=*tail;
		*tail=tmp;
	}
	
}
int main (void)
{
	int arr[10]={2,3,4,5,6,7,8,9,10,11};
	int m,n;
	scanf("%d %d",&m,&n);
	int i;
	for(i=0;i<10;i++)
	{
		printf("%d",arr[i]);	
	}
	printf("\n");
	fun(arr,m-1,n-1);
	
	for(i=0;i<10;i++)
	{
		printf("%d",arr[i]);	
	}
	printf("\n");
	return 0;
}

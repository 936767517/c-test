#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int array_init(int *arr,int n)
{
	int i;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		arr[i]=rand()%100;	
	}
	
}
void insert_arry(int arry[],int pos,int value)
{
	int i;
	for(i=8;i>pos;i--)
	{
		arry[i+1]=arry[i];
	}
	
		arry[pos+1]=value;
}
void array_print(int *arr,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d ",arr[i]);	
	}
	printf("\n");
}
int main(void)
{
	int arr[10]={};
	int pos;
	int value=11;
	scanf("%d",&pos);
	array_init(arr,10);
	array_print(arr,10);
	insert_arry(arr,pos,value);
	array_print(arr,10);
	return 0;	
}

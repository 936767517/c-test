#include<stdio.h>
int fun (int *arr)
{
	int *d=arr;
	printf("%d\n",d[2]);
}
int main()
{
	int arr[3]={1,2,3};
	fun(arr);
}

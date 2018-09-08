#include<stdio.h>
int main(void)
{
	int arr[4][6]={1,2,3,4,5};
	int arr1[5]={1,2,3,4,5};
	int *p=arr1;
	int (*q)[4][6]=&arr;
	printf("%d\n",*p[2]);
	printf("%p\n",q);
	printf("%p\n",&arr);
	
	return 0;	
}

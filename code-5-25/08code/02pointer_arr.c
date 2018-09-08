#include <stdio.h>

int main(void)
{
	int arr[] = {1,2,3,4,5,65,4,5,6,7,21,1,323};
	int *p = (int *)(arr + 1);
	int *q = (int *)(&arr + 1);

	printf(" arr = %p\n", arr); // 数组的首地址
	printf("&arr = %p\n", &arr); // 数组的地址
	printf("&arr[0] = %p\n", &arr[0]); // 数组的首地址

	printf("*p = %d\n", *(p - 1));
	printf("*q = %d\n", *(q - 1));
	
	return 0;
}

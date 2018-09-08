#include <stdio.h>

// 数组指针 : 指向数组的指针

int main(void)
{
	int arr1[3][5] = {};
	int arr[5] = {1,2,3,4,5};
	int *p = arr;
	int (*q)[5] = &arr;
	int (*q1)[3][5] = &arr1;

	//q = &arr1[0];
	q = arr1;

	printf("arr[2] = %d\n", (*q)[2]);
	printf("arr1[1][2] = %d\n", q[1][2]);

	return 0;
}

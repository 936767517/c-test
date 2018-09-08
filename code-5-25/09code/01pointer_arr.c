#include <stdio.h>

// 指针数组 ： 存储指针的数组

//void fun(int **arr)
void fun(int *arr[])
{
	printf("fun::arr[][] = %d\n", arr[2][1]);
}

int main(void)
{
	int n = 5;
	int m = 6;
	int arr1[3] = {1,2,3};
	int* arr2[4] = {&n, &m, arr1, NULL};
	int *p = arr1;
	int **q = arr2;

	fun(arr2);

	printf("n = %d\n", *arr2[0]);
	printf("m = %d\n", *arr2[1]);
	printf("m = %d\n", arr2[1][0]);
	printf("%d %d %d\n", arr2[2][0], arr2[2][1], arr2[2][2]);
	printf("%d\n", q[2][1]);
	
	return 0;
}

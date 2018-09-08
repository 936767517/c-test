#include <stdio.h>

void print_arr(int *arr, int len)
//void print_arr(int arr[], int len)
{
	int i;

	printf("print_arr():%d %d\n", sizeof(arr), sizeof(arr[0]));

	arr[0] = 5444444; // 形参可以修改实参数据
	for(i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(void)
{
	int arr1[5] = {};
	int arr2[6] = {0,1,2,3,4,5};
	int arr3[7] = {2,4,6,8};
	int arr4[8] = {0};
	int arr5[] = {1,2,3,43,5,6};
	int arr7[8] = {[2] = 6, [4] = 7};
	int len = sizeof(arr5)/sizeof(arr5[0]);

	int arr6[9] = {1,2,(3,4),(5,6),(7,8),9};

	printf("len = %d\n", len);

	// 数组名是一个常量
	 // arr4 = arr7; // error

	print_arr(arr1, 5);
	print_arr(arr2, 6);
	print_arr(arr3, 7);
	print_arr(arr4, 8);
	print_arr(arr5, len);
	print_arr(arr6, 9);
	print_arr(arr7, 8);
	
	printf("arr1[0] = %d\n", arr1[0]);

	return 0;
}

#include <stdio.h>

// int arr[]  =>  int *arr
// int* arr[3]  type arr[3]

//void print(int (*arr)[3], int x)
void print(int arr[][3], int x)
{
	int i, j;
	
	for(i = 0; i < x; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	int arr2[4][4] = {};
	int arr1[5][3] = {};
	int arr[4][3] = {};
	
	print(arr, 4);
	printf("===========\n");
	print(arr1, 5);

	return 0;
}

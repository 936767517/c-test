#include <stdio.h>

// int fun(int arr[])
// int fun(int *arr)


void array_init(int arr[][4], int len)
{
	int x, y;

	for(x = 0; x < len; x++)
	{
		for(y = 0; y < 4; y++)
		{
			arr[x][y] = x+y;
		}
	}
}

void array_print(int arr[][4], int len)
{
	int x, y;

	for(x = 0; x < len; x++)
	{
		for(y = 0; y < 4; y++)
		{
			printf("%d ", arr[x][y]);
		}
		printf("\n");
	}
}

int main(void)
{
	int arr[3][4] = {};
	int arr1[5][4] = {{1,2,3,4},
					  {2,3,4,5},
					  {3,4,5,6},
					  {4,5,6,7},
					  {5,6,7,8}};
	int arr2[2][4] = {1,2,3,4,5,6,7,8};
	int arr3[3][4] = {
			[0] = {1,2,3,4},
			[2] = {[0] = 5,
					[3] = 9
					}
			};
	int arr4[][4] = {1,2,3,4,5,5,6,7,7,8,8,9,3,3,4,4,4,4,4,4,4,4,4,5};

	printf("sizeof(arr4[0][0]) = %d\n", sizeof(arr4[0][0]));
	printf("sizeof(arr4[0])    = %d\n", sizeof(arr4[0]));
	printf("sizeof(arr4)       = %d\n", sizeof(arr4));

	array_init(arr, 3);

	array_print(arr, 3);
	printf("================\n");
	array_print(arr1, 5);
	printf("================\n");
	array_print(arr2, 2);
	printf("================\n");
	array_print(arr3, 3);
	printf("================\n");
	array_print(arr4, sizeof(arr4)/sizeof(arr4[0]));

	return 0;
}

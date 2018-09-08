#include <stdio.h>

//void print_arr(int array[], int len)
void print_arr(int *array, int len)
{
	int i;

	array[0]  = 23;
	for(i = 0; i < len; i++)
	{
		printf("%d ", array[i]); // *(array + i)
	}
	printf("\n");
}

int main(void)
{
	int i;
	int arr[7];
	int arr1[10] = {};

	for(i = 0; i < 7; i++)
	{
		arr[i] = 2 * i + 1;
	}

	printf("arr[0] = %d\n", arr[0]);
	print_arr(arr, 7);
	print_arr(arr1, 10);
	printf("arr[0] = %d\n", arr[0]);
	
	return 0;
}

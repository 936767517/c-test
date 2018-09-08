#include <stdio.h>

void init_array(int arr[], int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		scanf("%d", &arr[i]);
	}
}

int get_div(int arr1[], int x, int arr2[], int y)
{
	int i;

	for(i = 0; i < y; i++)
	{
		if(0 == arr1[i])
		{
			return -1;
		}
		arr2[i] = arr1[ i+1 ] / arr1[i];
	}
	return 0;
}

void print_array_3(int arr[], int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
		if((i+1) % 3 == 0)
		{
			printf("\n");
		}
	}
}

int main(void)
{
	int arr_a[10];
	int arr_b[10];

	init_array(arr_a, 10);
	
	if(0 != get_div(arr_a, 10, arr_b, 9))
	{	
		printf("there is an 0 in array\n");
		return -1;
	}

	print_array_3(arr_b, 9);
	
	return 0;
}

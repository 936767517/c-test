#include <stdio.h>

void init_arr(int arr[][5])
{
	int i, j;
	int value = 1;

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			arr[i][j] = value;
			value += 1;
		}
	}
}

void print_arr(int arr[][5])
{
	int i, j;

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j <= i; j++)
		{
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	int arr[5][5];

	init_arr(arr);

	print_arr(arr);
	
	return 0;
}

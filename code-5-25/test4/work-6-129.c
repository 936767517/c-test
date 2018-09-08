#include <stdio.h>

void init_arr(int arr[][3])
{
	int i, j;
	int value = 2;

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			arr[i][j] = value;
			value += 2;
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void print_arr(int arr[][3])
{
	int i, j;

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 2; j++)
		{
			printf("%d ", arr[j][i]);
		}
		printf("\n");
	}
}

int main(void)
{
	int arr[2][3];

	init_arr(arr);

	print_arr(arr);
	
	return 0;
}

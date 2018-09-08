#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void array_init(int arr[][4], int len)
{
	int x, y;

	srand( time(NULL) );
	for(x = 0; x < len; x++)
	{
		for(y = 0; y < 4; y++)
		{
			arr[x][y] = rand() % 10;
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

int get_max(int arr[][4], int len)
{
	int max = arr[0][0];
	int i, j;

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(max < arr[i][j])
			{
				max = arr[i][j];
			}
		}
	}
	return max;
}

void print_value_locations(int arr[][4], int len, int value)
{
	int i, j;

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(value == arr[i][j])
			{
				printf("(%d,%d)\n", i, j);
			}
		}
	}
}

int main(void)
{
	int max;
	int arr[3][4] = {};

	array_init(arr, 3);
	array_print(arr, 3);

	max = get_max(arr, 3);
	printf("max = %d\n", max);
	print_value_locations(arr, 3, max);
	
	return 0;
}

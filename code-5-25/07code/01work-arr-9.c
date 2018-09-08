#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8 

void array_init(int arr[][N], int len)
{
	int x, y;

	for(x = 0; x < len; x++)
	{
		for(y = 0; y < N; y++)
		{
			arr[x][y] = (x + y) % N + 1;
		}
	}
}

void array_print(int arr[][N], int len)
{
	int x, y;

	for(x = 0; x < len; x++)
	{
		for(y = 0; y < N; y++)
		{
			printf("%d ", arr[x][y]);
		}
		printf("\n");
	}
}

int main(void)
{
	int max;
	int arr[N][N] = {};

	array_init(arr, N);
	array_print(arr, N);

	return 0;
}

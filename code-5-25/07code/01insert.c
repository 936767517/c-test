#include <stdio.h>

#define GAMESIZE 10

// @x : [0, GAMESIZE-1]
// @y : [0, GAMESIZE-1]
int insert(int dest[][GAMESIZE], int src[][4], int x, int y)
{
	int i, j;

	if(x >= 0 && x+3 < GAMESIZE && y >= 0 && y+3 < GAMESIZE)
	{
		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 4; j++)
			{
				dest[x+i][y+j] = src[i][j];
			}
		}
		return 0;
	}
	return -1;
}

void print_arr(int arr[][GAMESIZE])
{
	int i, j;

	for(i = 0; i < GAMESIZE; i++)
	{
		for(j = 0; j < GAMESIZE; j++)
		{
			printf("%d", arr[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	int x, y;
	int arr1[GAMESIZE][GAMESIZE] = {};
	int arr2[4][4] = {1,2,3,4,
					  2,3,4,5,
					  3,4,5,6,
					  4,5,6,7};
	
	scanf("%d %d", &x, &y);

	insert(arr1, arr2, x, y);
	
	print_arr(arr1);

	return 0;
}

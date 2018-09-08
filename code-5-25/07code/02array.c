#include <stdio.h>

//char graphic[7][4][4][4];
char graphic[28][4][4] = {
		[0] = {
				{0,1,0,0},
				{1,1,1,0},
				{0,0,0,0},
				{0,0,0,0}
			},
		[1] = {
				{0,1,0,0},
				{0,1,1,0},
				{0,1,0,0},
				{0,0,0,0}
			},
		[2] = {
				{0,0,0,0},
				{1,1,1,0},
				{0,1,0,0},
				{0,0,0,0}
			},
		[3] = {
				{0,1,0,0},
				{1,1,0,0},
				{0,1,0,0},
				{0,0,0,0}
			},
		};

void change(char arr[][4])
{
	int i, j;
	int b[4][4] = {};

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			b[j][3-i] = arr[i][j];
		}
	}
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			arr[i][j] = b[i][j];
		}
	}
}

void print(char arr[][4])
{
	int i,j;

	printf("==========\n");
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			switch(arr[i][j])
			{
				case 1:
					printf("[]"); break;
				case 0:
					printf("  "); break;
			}
		}
		printf("\n");
	}
}

int main(void)
{
#if 0
	while(1)
	{
		print(graphic[0]);
		change(graphic[0]);
		sleep(1);
	}
#else
	int i = 0;
	while(1)
	{
		// i = i / 4 * 4 + (i+1)%4
		print(graphic[i % 4]);
		i++;
		sleep(1);
	}
#endif
	return 0;
}


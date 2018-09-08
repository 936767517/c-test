/*
 * chess
 * 
 * */

#include <stdio.h>

int main(void)
{
	int a, b;

	for(a = 1; a <= 9; a++)
	{
		for(b = 1; b <= 9; b++)
		{
			if(a % 3 != b % 3)
			{
				printf("[%d,%d]", a, b);
			}
		}
		printf("\n");
	}
	
	return 0;
}

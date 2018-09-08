/*
 * chess
 * 
 * */

#include <stdio.h>

#define NUM 81
int main(void)
{
	int a = 0;

#if 0
	for(; a % 10 < 9; a++) // ge
	{
		for(a %= 10; a / 10 < 9; a += 10) // shi
		{
			if((a % 10) % 3 != (a / 10) % 3)
			{
				printf("[%d,%d]", (a % 10), (a / 10));
			}
		}
	}
#else
	for(; a / 10 < 9; a += 10) // shi
	{
		for(a = a/10*10; a % 10 < 9; a++)  // ge
		{
			if((a % 10) % 3 != (a / 10) % 3)
			{
				printf("[%d,%d]", (a % 10)+1, (a / 10)+1);
			}
		}
	}

#endif

	return 0;
}

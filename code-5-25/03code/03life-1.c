/*
 * chess
 * 
 * */

#include <stdio.h>

#define NUM 81
int main(void)
{
	int a;

#if 0
	for(a = 0; a < NUM; a++)
	{
		if((a / 9) % 3 != (a % 9) % 3)
		{
			printf("[%d %d]",(a / 9), (a % 9));
		}

		if(a % 10 == 0)
		{
			printf("\n");	
		}
	}
#else
	a = 81;

	while(a--)
	{
		if((a / 9) % 3 != (a % 9) % 3)
		{
			printf("[%d %d]",(a / 9), (a % 9));
		}
	}
#endif
	
	return 0;
}

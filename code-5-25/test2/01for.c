#include <stdio.h>

/*
 * for(init ; cond; inc)
 * {
 *		exprs;
 * }
 * 
 * */

int main(void)
{
	int i = 0;

	for( i = 0 ; i < 10; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	
	return 0;
}

#include <stdio.h>

int main(void)
{
	int i; // 随机数

	// init cond
	i = 1;
	while(i <= 10) // while( cond )
	{
		printf("%d ", i); // exprs;
		i++; // inc
	}

	printf("\ni = %d\n", i);
	
	return 0;
}

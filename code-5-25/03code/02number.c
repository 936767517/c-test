#include <stdio.h>

int main(void)
{
	int i, j;
	int sum;

	for(i = 2; i <= 1000; i++)
	{
		sum = 0;
		for(j = 1; j <= i/2; j++)
		{
			if(0 == i % j)
			{
				sum += j;
			}
		}
		if(sum == i)
		{
			printf("%d\n", sum);
		}
	}
	
	return 0;
}

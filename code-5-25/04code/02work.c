#include <stdio.h>

int get_max(int a, int b, int c)
{
	if(a >= b && a >= c)
	{
		return a;
	}
	else if(b >= c)
	{
		return b;
	}
	else
	{
		return c;
	}
}

int main(void)
{
	int val1, val2, val3;
	int max;

	scanf("%d %d %d", &val1, &val2, &val3);

	max = get_max(val1, val2, val3);
	
	printf("max = %d\n", max);
	
	return 0;
}

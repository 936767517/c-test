#include <stdio.h>

int sum(int n)
{
	int i;
	int sum = 0;

	for(i = 1; i <= n; i++)
	{
		sum += i;
	}
	return sum;
}

int main(void)
{
	int a = 100;
	int b;

	b = sum(a);
	printf("b = %d\n", b);
	
	return 0;
}

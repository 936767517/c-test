#include <stdio.h>

int fabonacci(int n)
{
	int i;
	int a = 1;
	int b = 1;
	int c;

	for(i = 2; i <= n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

int main(void)
{
	int i;
	int n;

	scanf("%d", &n);


	for(i = 0; i < n; i++)
	{
		printf("%d ", fabonacci(i) );
	}
	printf("\n");
	
	return 0;
}

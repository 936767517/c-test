#include <stdio.h>

int main(void)
{
	int a, b;
	int res;

	scanf("%d %d", &a, &b);

	res = a * a + b * b;

	printf("a*a+b*b = %d\n", res);
	if(res > 100)
	{
		printf("res = %d\n", res / 100);
	}
	else
	{
		printf("a+b = %d\n", a + b);
	}
	
	return 0;
}

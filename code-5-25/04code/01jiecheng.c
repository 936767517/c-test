#include <stdio.h>

int fun(int n)
{
	if(0 == n || 1 == n)
		return 1;
	return n*fun(n-1);
}

int fun1(int n)
{
	if(n > 1)
		return n*fun(n-1);
	return 1;
}

int main(void)
{
	int n;
	int res;

	scanf("%d", &n);

	res = fun1(n);

	printf("res = %d\n", res);
	
	return 0;
}

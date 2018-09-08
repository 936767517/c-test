#include <stdio.h>

// max = x>y?x:y;
// x>y ? max=x : max=y; 

int fun(int x, int y)
{
	/*
	if(x > y)
	{
		return (x - y);
	}
	else // x <= y
	{
		return (y - x);
	}
	*/
	return ( x > y ? (x-y) : (y-x) );
}

int main(void)
{
	int a, b;
	int c;

	scanf("%d %d", &a, &b);

	c = fun(a, b);
	printf("c = %d\n", c);

	return 0;
}

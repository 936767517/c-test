#include <stdio.h>

#include "itoa.h"

void itoa(int n)
{
	if(n < 0)
	{
		printf("- ");
		n *= -1;
	}

	if(n / 10 != 0)
	{
		itoa( n/10 );
	}
	printf("%c ", n%10 + '0');
}

int add(int a, int b)
{
	strlen("abc");
	struct node n2 = {a, b};
	return a+b;
}

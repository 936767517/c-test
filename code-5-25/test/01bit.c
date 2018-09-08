#include <stdio.h>

int main(void)
{
	int a = 5;

	int b = a | 2;
	b = a | (1 << (2-1));
	int c = a << 1;
	int d = a & (~4);
	d = a & (~(1 << (3-1)));

	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);
	printf("d = %d\n", d);
	
	return 0;
}

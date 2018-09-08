#include <stdio.h>

int main(void)
{
	int a = 3;
	int b = 5;

	printf("a = %d, b = %d\n", a, b);

#if 1
	a = a + b;
	b = a - b;
	a = a - b;
#else
	int tmp = a;
	a = b;
	b = tmp;
#endif

	printf("a = %d, b = %d\n", a, b);
	
	return 0;
}

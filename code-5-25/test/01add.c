#include <stdio.h>

int main(void)
{
	int a = 5;

	printf("a = %d\n", a);
	a = a + 1;
	printf("a = %d\n", a);
	a++;
	printf("a = %d\n", a);
	a += 1; // a = a + 1;
	printf("a = %d\n", a);
	
	return 0;
}

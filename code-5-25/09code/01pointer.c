#include <stdio.h>

int main(void)
{
	int n = 5;
	int *p = &n;
	int * * q = &p;

	printf("n = %d\n", n); // 5
	printf("&n = %p\n", &n); // &n
	printf("*p = %d\n", *p); // n
	printf("&p = %p\n", &p); // &p
	printf("q = %p\n", q); // &p
	printf("*q = %p\n", *q); // &n
	printf("**q = %d\n", **q); // n
	
	return 0;
}

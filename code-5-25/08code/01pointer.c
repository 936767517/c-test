#include <stdio.h>

int main(void)
{
	int n = 6;
	int *p = &n;
	// int *p; p = &n;
	
	printf("&n = %p\n", &n);
	printf(" p = %p\n", p);

	// scanf("%d", &n);  

	*p = 8;
	p[0] = 10;
	printf("n = %d\n", n);

	return 0;
}

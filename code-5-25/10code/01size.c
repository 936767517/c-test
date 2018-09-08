#include <stdio.h>

int main(void)
{
	int i;
	short s;
	int ii;

	size_t i1 = (size_t)&i;
	//size_t s1 = (size_t)&s;
	
	printf("%lu %p %lf\n", &i, &i, (float)i1 / 4.0);
	//printf("%lu %p %lf\n", &s, &s, (float)s1 / 4);
	
	printf("%p\n%p\n%p\n", &i, &s, &ii);

	return 0;
}

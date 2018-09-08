#include <stdio.h>

int main(void)
{
	int i;
	double d[2];
	char str[20] = "sldjfsd";
	int arr[5] = {1,2,3,4,5};
	int *p = arr;
	char *q = str;
	double *m = d;

	printf("%d %d %d\n", sizeof(p), sizeof(q),sizeof(m));

	printf("%d(int *)    %p %p\n", sizeof(int), p, p + 1);
	printf("%d(char *)   %p %p\n", sizeof(char), q, q + 1);
	printf("%d(double *) %p %p\n", sizeof(double), m, m + 1);

	for(i = 0; i < 5; i++, p++)
	{
		printf("%d ", *p);
	}
	printf("\n");
	
	return 0;
}

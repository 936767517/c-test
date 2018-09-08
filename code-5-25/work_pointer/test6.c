#include <stdio.h>

int *findmax(int *s, int t, int *k)
{
	int max = *s;
	int *maxp = s;
	int *p;
	
	for(p = s; p < s+t; p++)
	{
		if(max < *p)
		{
			max = *p;
			maxp = p;
		}
	}
	*k = maxp - s;
	return maxp;
}

int main()
{
	int a[10] = {12, 23,34,45,56,67,78,89,11,22};
	int len = 10;
	int k;
	int *add;

	add = findmax(a, len, &k);

	printf("%d,%d,%p\n", a[k], k, add);
	
	return 0;
}

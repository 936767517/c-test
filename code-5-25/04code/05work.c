#include <stdio.h>

int get_count(int n)
{
	int i;
	int count = 2;

	if(n == 1)
		return 1;

	for(i = 2; i <= n/2; i++)
	{
		if(n % i == 0)
		{
			count++;
		}
	}
	return count;
}

int is_primer(int n)
{
	if(2 == get_count(n))
		return 1;
	return 0;
}

int main(void)
{
	int n;
	int res;

	scanf("%d", &n);

	res = is_primer(n);
	printf("res = %d\n", res);
	
	return 0;
}

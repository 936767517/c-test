#include <stdio.h>

int fabonacci(int n)
{
	if(0 == n || 1 == n)
		return 1;
	return ( fabonacci(n-1)+fabonacci(n-2) );
}

int main(void)
{
	int i;
	int n;

	scanf("%d", &n);


	for(i = 0; i < n; i++)
	{
		printf("%d ", fabonacci(i) );
	}
	printf("\n");
	
	return 0;
}

#include <stdio.h>

void itoa(int n)
{
	if(n < 0)
	{
		printf("- ");
		n *= -1;
	}

	if(n / 10 != 0)
	{
		itoa( n/10 );
	}
	printf("%c ", n%10 + '0');
}

int main(void)
{
	int n;

	scanf("%d", &n);

	itoa(n);
	
	return 0;
}

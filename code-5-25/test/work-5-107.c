#include <stdio.h>

int main(void)
{
	int i = 1;
	int x, y;
	int sum = 1;

	scanf("%d %d", &x, &y);

	while(i <= y)
	{
		sum = sum * x;
		
		i++;
	}

	printf("%03d\n", sum % 1000);
	
	return 0;
}

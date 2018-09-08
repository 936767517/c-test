#include <stdio.h>

int main(void)
{
	int i = 3;
	int days = 0;
	int sum = 0;
	int each = 20;

	scanf("%d", &days);

	while(i <= days)
	{
		sum = sum + each;
		each = each * 2;
		i++;
	}

	printf("sum = %d\n", sum);
	
	return 0;
}

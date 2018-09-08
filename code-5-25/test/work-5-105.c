#include <stdio.h>

int main(void)
{
	int sum = 0;
	int days = 0;
	int each = 2;

	while( (sum+each) <= 100)
	{
		sum = sum + each;
		each *= 2;
		days ++;
	}
	printf("sum = %d\t days = %d\n", sum, days);

	printf("%f\n", 0.8 * ((float)sum / days));
	
	return 0;
}

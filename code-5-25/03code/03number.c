#include <stdio.h>

int main(void)
{
	unsigned int num;
	unsigned int sum = 0;
	unsigned int val;

	scanf("%u", &num);
	val = num;

	while(0 != num)
	{
		sum = sum * 10 + num % 10;
		num /= 10;
	}
	printf("sum = %d\n", sum);
	if(val == sum)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
	
	return 0;
}

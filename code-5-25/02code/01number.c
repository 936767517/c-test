#include <stdio.h>

// 三位水仙化数

int main(void)
{
	int num;
	int a, b, c;

	for(num = 100; num <= 999; num++)
	{
		a = num / 100;
		b = num / 10 % 10;
		c = num % 10;
		if(num == a*a*a + b*b*b + c*c*c)
		{
			printf("%d\n", num);
		}
	}
	
	return 0;
}

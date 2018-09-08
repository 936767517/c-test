#include <stdio.h>

int main(void)
{
	int num;
	int shi, ge;

	scanf("%d", &num);
	printf("num = %d\n", num);

	shi = num / 10;
	ge = num % 10;

	printf("shi = %d\n", shi);
	printf("ge = %d\n", ge);
	
	return 0;
}

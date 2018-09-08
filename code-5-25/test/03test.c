#include <stdio.h>

int main(void)
{
	int num;
	int bai, shi, ge;

	printf("please input a number(100~999):");
	scanf("%d", &num);

	bai = num / 100;
	//shi = num / 10 % 10;
	shi = num % 100 / 10;
	ge  = num % 10;

	printf("bai = %d\n", bai);
	printf("shi = %d\n", shi);
	printf("ge = %d\n", ge);
	
	return 0;
}

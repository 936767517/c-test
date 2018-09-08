#include <stdio.h>

int main(void)
{
	int num;
	int flag = 1;// 1:+ 0:-

	scanf("%d", &num);

	if(num < 0)
	{
		flag = 0;
		num *= -1;
	}

	while(num > 0)
	{
		printf("%d ", num % 10);

		num /= 10;
	}
	if(flag == 0)
	{
		printf("-");
	}
	printf("\n");
	
	return 0;
}

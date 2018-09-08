#include <stdio.h>

int fun(int num)
{
	int sum = 1;

	if(num < 0)
	{
		return -1;
	}

	while(num != 0)
	{
		sum *= num;
		num--;
	}
	return sum;
}

int main(void)
{
	int num;
	int res;

	scanf("%d", &num);

	res = fun(num);
	if(-1 == res)
	{
		printf("fun() input data error\n");
	}
	else
	{
		printf("%d! = %d\n", num, res);
	}
	
	return 0;
}

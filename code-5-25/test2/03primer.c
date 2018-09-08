#include <stdio.h>

int is_primer(int num);

int main(void)
{
	int i;
	int res;
	for(i = 2; i < 100; i++)
	{
		res = is_primer(i);
		if(1 == res)
		{
			printf("%d ", i);
		}
	}
	printf("\n");

	return 0;
}
int is_primer(int num)
{
	int i;
	int flag = 1;
	for(i = 2; i <= num/2; i++)
	{
		if(num % i == 0)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

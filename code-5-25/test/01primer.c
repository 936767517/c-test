#include <stdio.h>

int main(void)
{
	int i = 2;
	int num;
	int flag = 1; // 0:N 1:Y

	scanf("%d", &num);

	if(num <= 1)
	{
		printf("input data error\n");
		return -1;
	}

	while(i < (num/2+1))
	{
		if(num % i == 0)
		{
			flag = 0;
			break;
		}

		i++;
	}

	if(flag == 1)
	{
		printf("is primer\n");
	}
	else
	{
		printf("not primer\n");
	}
	
	return 0;
}

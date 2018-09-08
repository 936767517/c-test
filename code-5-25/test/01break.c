#include <stdio.h>

int main(void)
{
	int i; // 随机数

	i = 1;
	while(i <= 10)
	{
		if(i == 4)
		{
			break;
		}
		printf("%d ", i);
		i++; 
	}

	printf("\ni = %d\n", i);
	
	return 0;
}

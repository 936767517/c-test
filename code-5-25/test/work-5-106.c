#include <stdio.h>

int main(void)
{
	int i = 1;
	int res;

	while(i <= 99)
	{
		res = i * i;
		if(i < 10 && res%10 == i)
		{
			printf("i = %d\n", i);
		}
		else if(res % 100 == i)
		{
			printf("i = %d\n", i);
		}

		i++;
	}
	
	return 0;
}

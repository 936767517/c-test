#include <stdio.h>

int main(void)
{
	int flag;
	int n;
	int i;
	int count = 0;

	for(n = 2; n <= 100; n++)
	{
		for(flag = 1, i = 2; i < n/2+1; i++)
		{
			if(n % i == 0)
			{
				flag = 0;
				break;
			}
		}
		//if(flag == 1)
		if(1 == flag)
		{
			count++;
			//printf("%d ", n);
		}
	}

	printf("count = %d\n", count);

	return 0;
}

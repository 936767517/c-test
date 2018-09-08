#include <stdio.h>

int main(void)
{
	int n;
	int count1 = 0, count2 = 0;
	int sum1 = 0, sum2 = 0;
	float ave1 = 0, ave2 = 0;

	while(1)
	{
		scanf("%d", &n);
		if(0 == n)
		{
			break;
		}

		if(n % 2 == 1)
		{
			count1++;
			sum1 += n;
		}
		else
		{
			count2++;
			sum2 += n;
		}
	}
	
	if(count1 != 0)
	{
		ave1 = (float)sum1 / count1;
	}
	if(count2 != 0)
	{
		ave2 = (float)sum2 / count2;
	}

	printf("奇数 %d %f\n", count1, ave1);
	printf("偶数 %d %f\n", count2, ave2);

	return 0;
}

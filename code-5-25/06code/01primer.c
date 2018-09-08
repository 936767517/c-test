#include <stdio.h>

int main(void)
{
	int i, j;
	int arr[100] = {1,1};
	
	for(i = 2; i < 100; i++)
	{
		if(arr[i] == 0)
		{
			for(j = i + i; j < 100; j += i)
			{
				arr[j] = 1;
			}
		}
	}
	for(i = 0; i < 100; i++)
	{
		if(arr[i] == 0)
		{
			printf("%d ", i);
		}
	}
	printf("\n");

	return 0;
}

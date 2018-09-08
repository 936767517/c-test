#include <stdio.h>

int main(void)
{
	int j = 0;
	int i = 0;
	int num;
	int arr[32] = {};

	scanf("%d", &num);
	
	while(0 != num)
	{
		arr[i++] = num % 10;
		num /= 10;
	}

	for(i--; j < i; j++, i--)
	{
		if(arr[i] != arr[j])
		{
			printf("no\n");
			return 0;
		}
	}
	printf("yes\n");

	return 0;
}

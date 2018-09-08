#include <stdio.h>

// 数组：具有相同数据类型的有序的集合，数组名作为唯一的标识

int main(void)
{
	int i = 0;
	int num;
	int arr[10];

	scanf("%d", &num);

	while(num > 0)
	{
		arr[i] = num % 10;
		i++;
		//printf("%d ", num % 10);
		num /= 10;
	}

	while(--i >= 0)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;
}

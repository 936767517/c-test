#include <stdio.h>

#include "array.h"

void move_left_(int *arr, int len)
{
	int i;
	int tmp = arr[0];

	for(i = 1; i < len; i++)
	{
		arr[i - 1] = arr[i];
	}
	arr[len - 1] = tmp;
}

void move_left(int *arr, int len, int n)
{
	if(n < 0)
		return ;
	
	n = n % len;

	while(n--)
	{
		move_left_(arr, len);
	}
}

int main(void)
{
	int n;
	int arr[10] = {};

	array_init(arr, 10);
	array_print(arr, 10);

	scanf("%d", &n);

	move_left(arr, 10, n);

	array_print(arr, 10);
	
	return 0;
}

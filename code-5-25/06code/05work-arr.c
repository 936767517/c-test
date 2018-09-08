#include <stdio.h>

#include "array.h"

int array_insert(int *arr, int pos, int value)
{
	int i;

	if(pos < 0 || pos >= 5)
	{
		return -1;
	}

	for(i = 5-1; i > pos; i--)
	{
		arr[i + 1] = arr[i];
	}
	arr[pos + 1] = value;
	return 0;
}

int main(void)
{
	int pos;
	int value;
	int arr[10] = {};

	array_init(arr, 5);
	array_print(arr, 5);

	scanf("%d %d", &pos, &value);

	array_insert(arr, pos, value);

	array_print(arr, 6);

	
	return 0;
}

#include <stdio.h>

#include "array.h"

int main(void)
{
	int i;
	int max_;
	int arr[10] = {};

	array_init(arr, 10);
	array_sort2(arr, 10);
	array_print(arr, 10);

	for(i = 1; i < 10; i++)
	{
		if(arr[i] != arr[0])
		{
			max_ = arr[i];
			break;
		}
	}
	printf("max_ = %d\n", max_);

	
	return 0;
}

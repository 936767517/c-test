#include <stdio.h>

#include "array.h"

int main(void)
{
	int arr[] = {1, 4, 2, 4, 3, 5, 2, 6, 6, 7, 9, 3};

	//array_print(arr, sizeof(arr)/sizeof(arr[0]));

	//array_sort1(arr, sizeof(arr)/sizeof(arr[0]));
	//array_sort2(arr, sizeof(arr)/sizeof(arr[0]));
	
	quick_sort_(arr, sizeof(arr)/sizeof(arr[0]));

	//array_print(arr, sizeof(arr)/sizeof(arr[0]));

	return 0;
}

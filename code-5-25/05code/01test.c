#include <stdio.h>

#include "array.h"

int main(void)
{
	int arr[10];

	array_init(arr, 10);

	array_print(arr, 10);
	
	return 0;
}

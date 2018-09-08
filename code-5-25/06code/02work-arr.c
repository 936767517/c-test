#include <stdio.h>

#include "array.h"

int main(void)
{
	int i;
	int arr[20] = {};
	int len;
	int count1 = 0;
	int count2 = 0;

	srand( time(NULL) );
	len = rand() % 11 + 10;

	array_init(arr, len);
	array_print(arr, len);

	for(i = 0; i < len; i++)
	{
		if(arr[i] < 0)
		{
			count1++;
		}
		else if(1 == arr[i] % 2 )
		{
			count2++;
		}
	}
	printf("count1 = %d, count2 = %d\n", count1, count2);
	
	return 0;
}

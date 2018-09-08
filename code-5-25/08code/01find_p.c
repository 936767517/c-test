#include <stdio.h>

int main(void)
{
	int i;
	int arr[10] = {3,1,2,5,7,9,6,8,0,4};
	int *max = arr;
	int *min = arr;

	for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		if(*max < arr[i])
		{
			max = arr + i;
		}
		if(*min > arr[i])
		{
			min = arr + i;
		}
	}
	
	printf("max[%d] = %d \n", max - arr, *max);
	printf("min[%d] = %d \n", min - arr, *min);

	return 0;
}

#include <stdio.h>

#define N 10

int main(void)
{
	int i;
	int arr[N];

	printf("%d %d\n", sizeof(arr[0]), sizeof(arr));

	printf("&i = %p\n", &i);
	printf("&arr[11] = %p\n", &arr[11]);

	// for(i = 0; i < 12; i++) // error
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		arr[i] = 1;
	}

	for(i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;
}

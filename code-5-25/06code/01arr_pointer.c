#include <stdio.h>

int main(void)
{
	int i ;
	int arr[10] = {1,2,3,4,5,6,7,8,9,0};
	int *p = &arr[0];
	p = arr;
	
	for(i = 0; i < 10; i++)
	{
		printf("%d ", p[i]);
		printf("%d ", *(p+i));
	}
	printf("\n");

	return 0;
}

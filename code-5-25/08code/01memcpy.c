#include <stdio.h>
#include <string.h>

int main(void)
{
	int i;
	int arr[5] = {3,1,2,5,7};
	int str[6] = {};
	int *p;

	//p = (int *)memcpy(str, arr, sizeof(arr));
	p = (int *)memcpy(str, arr, 5*sizeof(*arr));

	for(i = 0; i < 6; i++)
	{
		printf("%d ", str[i]);
		printf("%d ", p[i]);
	}
	printf("\n");
	
	return 0;
}

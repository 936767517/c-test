#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int n = 19;
	int arr[5] = {3,1,2,5,7};
	int *p = NULL;

	//p = (int *)malloc( sizeof(arr) );
	p = (int *)calloc(5, sizeof(*arr));
	if(NULL == p)
	{
		printf("malloc failed\n");
		return -1;
	}
	printf("p = %p\n", p);
	printf("p[2] = %d\n", p[4]);

	memcpy(p, arr, sizeof(*arr) * 5);
	
	p = (int *)realloc(p, 6 * sizeof(*arr));
	if(NULL == p)
	{
		printf("realloc failed\n");
		return -2;
	}
	p[5] = n;

	for(i = 0; i < 6; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");

	free(p);
	free(NULL);

	return 0;
}

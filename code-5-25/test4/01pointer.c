#include <stdio.h>

int main(void)
{
	int arr[5] = {1,2,3,4,5};
	int a = 5;
	int* p;

	p = &a;

	*p = 14;

	printf("&a = %p\n", &a);
	printf(" a = %d\n",  a);

	printf(" p = %p\n",  p);
	printf("&p = %p\n", &p);
	printf("*p = %d\n", *p);

	p = arr;

	int i;
	for(i = 0; i < 5; i++)
	{
		//printf("%d ", p[i]);
		//printf("%d ", *(p+i));
		//printf("%d ", arr[i]);
		printf("%d ", *(arr+i));
	}
	printf("\n");






	
	return 0;
}

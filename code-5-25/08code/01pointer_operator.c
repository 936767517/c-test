#include <stdio.h>

// type *p;
// 当指针加减整型数字时，以步长为基本单位, 步长=sizeof(type)

int main(void)
{
	int arr[10] = {1,2,3,4,5,6,6,7,8,9};
	int *p = arr;

	printf("*p = %d\n", *p);
	printf("p = %p\n", p);
	p = p + 1;
	printf("*p = %d\n", *p);
	printf("p = %p\n", p);
	
	return 0;
}

#include <stdio.h>

// type *p;
// 当指针加减整型数字时，以步长为基本单位, 步长=sizeof(type)

int main(void)
{
	int arr[10] = {1,21,23,34,45,56,66,77,88,99};
	int *p = arr;

	printf("*p = %d\n", *p);
	//printf("*p++ = %d\n", *p++);
	//printf("(*p)++ = %d\n", (*p)++);
	printf("*(p++) = %d\n", *(p++));
	printf("*p = %d\n", *p);

	return 0;
}

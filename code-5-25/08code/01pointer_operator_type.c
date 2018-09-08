#include <stdio.h>

// type *p;
// 当指针加减整型数字时，以步长为基本单位, 步长=sizeof(type)
// 指针偏移  指针强转 

int main(void)
{
	char *str = "abcdefghijklmnopqrst";
	char *p1 = (char *)str;
	short *p2 = (short *)str;
	int *p3 = (int *)str;

	p1 += 1;
	p2 += 1;
	p3 += 1;

	// (char)*p2;
	printf("*p1 = %c\n", *(char *)p1); // b
	printf("*p2 = %c\n", *(char *)p2); // c
	printf("*p3 = %c\n", *(char *)p3); // e


	return 0;
}

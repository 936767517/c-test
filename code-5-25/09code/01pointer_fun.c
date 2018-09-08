#include <stdio.h>
#include <stdlib.h>

// 指针函数：返回值为指针的函数

// 返回的指针必须长期有效
int *fun()
{
	return malloc(12);
}

int main(void)
{
	
	return 0;
}

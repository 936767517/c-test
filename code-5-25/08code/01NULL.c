#include <stdio.h>

// #define NULL (0)
// #define NULL ((void *)0)

int main(void)
{
	int *p = NULL; // 可指向，不可访问

	//printf("*p = %d\n", *p); // error

	//*p = 1; // error
	
	return 0;
}

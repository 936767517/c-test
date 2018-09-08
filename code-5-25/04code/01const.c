#include <stdio.h>

const float pi = 3.1415;
// 只读变量：存储类型为const  常变量

int main(void)
{
	int a = 0;
	const int b = 0;

	//b = 6; // error

	printf("b = %d\n", b);
	
	return 0;
}

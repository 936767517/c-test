#include <stdio.h>

// 求某一个变量或者某种数据类型所占的内存空间(byte)

int main(void)
{
	int a;
	int res;

	res = sizeof(a);
	printf("size = %d\n", res);

	res = sizeof(char);
	printf("size = %d\n", res);
	
	return 0;
}

#include <stdio.h>

// 函数声明
int add(int n, int m);

int main(void)
{
	int a = 10;

	// 函数调用
	int res = add(5, a); // add::n=5 add::m=a
	// main::res = add::res
	printf("res = %d\n", res);

	return 0;
}

// 函数的定义:定义自包含单元(函数体)
int add(int n, int m)
{
	int res = m + n;
	return res;
}

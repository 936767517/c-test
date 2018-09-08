#include <stdio.h>
#include <string.h>

// 函数指针 ：指向函数的指针

typedef int FUN(int,int);

int add(int a, int b)
{
	return a+b;
}

int fun1(int a, int b, FUN *funp)
{
	return funp(a, b);
}

int fun2(int a, int b, int (*funp)(int,int) )
{
	return funp(a, b);
}

int main(void)
{
	int res;

	res = fun1(3, 5, add);
	printf("res = %d\n", res);

	printf("res = %d\n", fun2(5, 7, add) );

	return 0;
}

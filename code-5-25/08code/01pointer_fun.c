#include <stdio.h>

// 通过传递指针，实现形参变量修改实参变量的值
// 但其依然为值传递
void fun( int * p )
{
	*p = 8;
}

#if 0
int *fun1()
{
	int m = 5;
	int *p = &m;
	return p;
}

int *fun2()
{
	int m = 320;
	int *p = &m;
	return p;
}
#endif

// 当函数返回指针时，其指针必须长期有效
// 在函数结束瞬间是有效的
int *fun3(int *p)
{
	return p;
}

int main(void)
{
#if 1
	int n = 5;
	fun( &n ); // fun::p = main::&n
	printf("n = %d\n", n);
#endif

	int *p = NULL; // 只能指向，防止处于野指针状态，但不能读写
	
	*fun3( &n ) = 19;
	p = fun3( &n );
	printf("*p = %d\n", *p);
	printf("n = %d\n", n);

	//p = fun1();
	//fun2();
	//printf("*p = %d\n", *p);

	return 0;
}

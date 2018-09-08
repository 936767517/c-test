#include <stdio.h>

void fun1(int a)
{
	a = 6;
}

void fun2(int *p)
{
	printf("fun2():*p = %d\n", *p);
	*p = 10;
}

// 返回的指针必须长期有效
int* fun3(int *p)
{
	return p;
}

/*
int* fun4()
{
	int m = 5;
	int *p = &m;
	return p;
}
*/

int main(void)
{
	int a = 5;
	int *p;
	
	//fun1(a);
	
	fun2(&a);

	p = fun3(&a);

	printf("main():*p = %d\n", *p);
	printf("a = %d\n", a);

	return 0;
}

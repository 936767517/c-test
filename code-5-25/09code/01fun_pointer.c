#include <stdio.h>
#include <string.h>

// 函数指针 ：指向函数的指针

typedef int FUN(int,int);

int add(int a, int b)
{
	return a+b;
}

int main(void)
{
	char *str = "hello world";
	FUN *p = add;
	int (*q1)(int, int) = &add;
	int (*q2)() = add;
	// size_t strlen(const char *s);
	size_t (*funp)(const char *) = strlen;

	printf("len = %d\n", funp(str) );

	printf("%d\n", (*q2)(1,2) );
	printf("%d\n", q1(1,2) );

	return 0;
}

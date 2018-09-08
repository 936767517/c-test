#include <stdio.h>

// 全局性 隐藏性 

// 静态变量：其存储类型为static
// 作用域：其所属的代码块
// 生命周期：从定义开始到程序结束
// 初始化：未初始化被自动初始化为0/NULL，只会被定义一次
// 内存空间位置：静态存储区

void fun()
{
	auto int a = 1;
	static int b = 0;

	a++;
	b++;

	printf("a = %d, b = %d\n", a, b);
}

int main(void)
{
	fun();
	fun();
	
	return 0;
}

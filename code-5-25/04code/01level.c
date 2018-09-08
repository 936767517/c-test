#include <stdio.h>

// 递归：函数直接或者间接的调用自身
// 优点：复杂算法简单化
// 缺点：大量消耗时间和空间

void level(int n)
{
	printf("%d level is %p\n", n, &n);
	if(n > 0)
	{
		level(n - 1);
	}
	printf("%d LEVEL IS %p\n", n, &n);
}

int main(void)
{
	level(4);
	
	return 0;
}

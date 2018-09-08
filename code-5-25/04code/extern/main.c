#include <stdio.h>

void msg();

extern int msg_a;
// 引用外部的全局变量
// 该变量必须为全局非静态变量

int main(void)
{
	printf("main.c:main()msg_a = %d\n", msg_a);

	msg_a++;

	msg();
	
	printf("main.c:main()msg_a = %d\n", msg_a);

	return 0;
}

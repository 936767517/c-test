#include <stdio.h>

// 字符串 == 常量
// 由字符构成的整体，最后以‘\0‘作为结束标志 

int main(void)
{
	char arr1[20];
	char arr[] = "hello world";
	char *str = "hello world";
	static int a;

	// 从第一个非‘ ’或‘\n’开始直到第二个‘ ’或‘\n’结束
	// 数组越界问题
	scanf("%s", arr1);
	puts(arr1);

	getchar();

	gets(arr1);
	puts(arr1);

#if 0
	printf("&a  = %p\n", &a);
	printf("arr = %p\n", arr);
	printf("str = %p\n", str);

	arr[0] = 'H';
	 // str[0] = 'H'; // error

	printf("arr = %s\n", arr);
	printf("str = %s\n", str);
	//putchar(str[0]);
	puts(arr);
	puts(str);
#endif

	return 0;
}

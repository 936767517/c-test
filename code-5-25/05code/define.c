#include <stdio.h>

// 宏定义: 简单的文本替换
// 宏函数 sizeof()
// 没有类型限制  尽量没有';' 只能替换一行

#define M 5
#define N 5
#define PI 3.14
#define INT int
#define INTP int*
#define STRING "hello world\n"
#define NN N*N
#define getint(d) scanf("%d", &(d))
#define add(a, b) ((a) + (b))
#define mul(a, b) ((a) * (b))
#define then {
#define end }

int add1(int a, int b)
{
	return a+b;
}

int main(void)
{
	float pi = PI;
	int i = 0, j = 1;
	int num = N;
	INT val = num;
	INTP p = &val, *q = &num;

	num = NN;

	printf("num = %d\n", num);
	printf("val = %d\n", val);
	printf("N = %d\n", N);
	printf("STRING = %s\n", STRING);

	if(num == 25)
	then
		printf(STRING);
	end
	
	//getint(num);

	printf("res = %d\n", add(num ,10));
	printf("res = %f\n", add(4.13 ,3.14));
	printf("res = %d\n", mul(2+3 ,3+5));

	printf("num = %d\n", num);

	return 0;
}

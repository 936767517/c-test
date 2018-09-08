#include <stdio.h>

#define III int*

// 类型重定义
typedef int DataType;
typedef int* DTP;
typedef int INT, *INTP;
typedef int ARR[5];
// typedef int[5] ARR;
typedef int FUN(int *);


int main(void)
{
	INT num = 5;
	int m = 6;
	DataType n = 5;
	DTP p = &m;
	III pp = &n;
	INTP p1 = &m;
	ARR arr = {num, m, n, *p, *p1};

	int i;
	for(i = 0; i < 5; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");

	III q1 = &m, q2 = n;

	DTP m1 = &m, m2 = &n;
	
	return 0;
}

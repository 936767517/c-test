#include <stdio.h>

// return_type funname(...)

int add(int val1, int val2)
{
	int res = val1 + val2;

	return res;
}

int main(void)
{
	int a = 7;
	int num;

	num = add(3, a);
	printf("num = %d\n", num);
	
	return 0;
}

#include <stdio.h>

double mypow(double x, int y)
{
	int i;
	double sum = 1;

	for(i = 0; i < y; i++)
	{
		sum *= x;
	}
	return sum;
}

int main(void)
{
	double x = 5.0;
	int y = 2;
	double res;

	res = mypow(x, y);
	printf("res = %lf\n", res);
	
	return 0;
}

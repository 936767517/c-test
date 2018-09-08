#include <stdio.h>

int main(void)
{
	int x;

	scanf("%d", &x);

	if(x % 3 == 0)
	{
		printf("能被其中一个数(3)整除\n");
	}
	if(x % 5 == 0)
	{
		printf("能被其中一个数(5)整除\n");
	}
	if(x % 7 == 0)
	{
		printf("能被其中一个数(7)整除\n");
	}
	
	return 0;
}

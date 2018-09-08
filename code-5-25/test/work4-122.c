#include <stdio.h>

int main(void)
{
	int x;

	scanf("%d", &x);

	if(x % (3*5*7) == 0) // x%3==0 && x%5==0 && x%7==0
	{
		printf("能同时被3,5,7整除\n");
	}
	else if(x % (3*5) == 0)
	{
		printf("能被其中两数(3,5)整除\n");
	}
	else if(x % (3*7) == 0)
	{
		printf("能被其中两数(3,7)整除\n");
	}
	else if(x % (5*7) == 0)
	{
		printf("能被其中两数(5,7)整除\n");
	}
	else if(x % 3 == 0)
	{
		printf("能被其中一个数(3)整除\n");
	}
	else if(x % 5 == 0)
	{
		printf("能被其中一个数(5)整除\n");
	}
	else if(x % 7 == 0)
	{
		printf("能被其中一个数(7)整除\n");
	}
	else
	{
		printf("不能被(3,5,7)任何一个整除\n");
	}
	
	return 0;
}

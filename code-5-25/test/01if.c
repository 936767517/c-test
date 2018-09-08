#include <stdio.h>

int main(void)
{
	int a = 0;

	scanf("%d", &a);

	if(a < 20)
	{
		printf("a < 20\n");
		if(a < 10)
		{
			printf("0 < a < 10\n");
		}
		else
		{
			printf("10 < a < 20\n");
		}
	}


	if( a == 10 )
	{
		printf("a == 10\n");
	}
	else if(a == 20)
	{
		printf("a == 20\n");
	}
	else
	{
		printf("a != 10 / 20\n");
	}
	
	return 0;
}

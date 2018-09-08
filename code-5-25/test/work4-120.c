#include <stdio.h>

int main(void)
{
	int a;

	scanf("%d", &a);

	//if(a % 5 == 0 && a % 7 == 0)
	if(a % (5 * 7) == 0)
	{
		printf("Yes\n");
	}
	else
	{
		printf("no\n");
	}
	
	return 0;
}

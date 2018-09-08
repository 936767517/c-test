#include <stdio.h>

int main(void)
{
	int i, j;

	if(4 == i)
	{
		//break; // error
		//continue; // error
	}

	for(j = 0; j < 5; j++)
	{
		for(i = 0; i < 10; i++)
		{
			if(4 == i)
			{
				break;
				//continue;
			}
			printf("%d ", i);
		}
		printf("\n");
	}

	return 0;
}

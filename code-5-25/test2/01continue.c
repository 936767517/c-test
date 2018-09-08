#include <stdio.h>

int main(void)
{
	int i = 0;

	while(i++ < 10)
	{
		if(i == 4)
		{
			//break;
			continue;
		}
		
		printf("%d ", i);
	}
	printf("\n");
	
	return 0;
}

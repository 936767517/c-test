#include <stdio.h>

int main(void)
{
	int chicken, hen, cock;

	printf("chicken\then\tcock\n");
	for(hen = 0; hen <= 100/3; hen++)
	{
		for(cock = 0; cock <= 100/5; cock++)
		{
			chicken = (100 - hen*3 - cock*5) * 3;
			if(100 == hen + cock + chicken)
			{
				printf("%d\t%d\t%d\n",
					chicken, hen,cock);
			}
		}
	}
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int num;
	int *p = NULL;
	int count = 0;

	// get data
	while(1)
	{
		// get input data & if
		scanf("%d", &num);
		if(0 == num)
		{
			break;
		}

		// add mem & store data
		count++;
		p = (int *)realloc(p, sizeof(int) * count);
		if(NULL == p)
		{
			return -1;
		}
		p[count - 1] = num;
	}

	// output data
	for(i = 0; i < count; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");

	free(p);
	
	return 0;
}

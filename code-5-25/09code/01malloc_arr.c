#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int i;
	int num;
	int *p = NULL;
	int *q = NULL;
	int count = 0;

	while(1)
	{
		scanf("%d", &num);
		if(0 == num)
		{
			break;
		}

		count++;
		q = p;
		p = (int *)malloc(count * sizeof(int));
		if(NULL == p)
		{
			free(q);
			return -1;
		}
		memcpy(p, q, sizeof(int)*(count-1));
		p[count-1] = num;
		free(q);
	}

	for(i = 0; i < count; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
	
	free(p);
	
	return 0;
}

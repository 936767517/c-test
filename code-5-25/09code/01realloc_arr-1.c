#include <stdio.h>
#include <stdlib.h>

typedef int DT;
#define SIZE (sizeof(DT)*15)

void get_DT(DT *n)
{
	scanf("%d", n);
}
void print_DT(DT *n)
{
	printf("%d ", *n);
}

int main(void)
{
	int i;
	DT num;
	DT *p = NULL;
	int count = 0;
	int n = 0;
	
	while(1)
	{
		get_DT(&num);
		if(0 == num)
		{
			break;
		}
		count++;

		if(count*sizeof(DT) > SIZE * n)
		{
			p = (DT *)realloc(p, SIZE*(++n));
			if(NULL == p)
			{
				return -2;
			}
		}
		p[count - 1] = num;
	}
	p = (DT *)realloc(p, count*sizeof(DT));
	if(NULL == p)
	{
		return -3;
	}

	for(i = 0; i < count; i++)
	{
		print_DT(p+i);
	}
	printf("\n");

	free(p);

	return 0;
}

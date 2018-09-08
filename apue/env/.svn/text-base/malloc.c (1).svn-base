#include <stdio.h>
#include <stdlib.h>


int main()
{
	int *p = NULL;

	p = malloc(sizeof(int));
	if(p == NULL)
	{
		exit(1);
	}

	*p = 1;

	printf("p = %p\t*p = %d\n",p,*p);

	free(p);
	p = NULL;

	*p = 100;
	printf("p = %p\t*p = %d\n",p,*p);

	exit(0);
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_mem(char **q, int size)
{
	printf("get_mem::q = %p\n", *q);
	*q = (char *)malloc(size);
	/* if error */
	printf("get_mem::q = %p\n", *q);
}

void free_mem(char **q)
{
	free(*q);
}

int main(void)
{
	char *p = NULL;
	char *str = "hello world";

	printf("main::p = %p\n", p);
	get_mem(&p, strlen(str)+1 );
	printf("main::p = %p\n", p);
	strcpy(p, str);

	puts(p);
	
	free_mem(&p);

	return 0;
}

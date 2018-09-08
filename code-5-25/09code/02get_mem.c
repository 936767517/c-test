#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *STRING;

void get_mem(STRING *q, int size)
{
	//printf("get_mem::q = %p\n", *q);
	*q = (STRING)malloc(size);
	/* if error */
	//printf("get_mem::q = %p\n", *q);
}

void free_mem(STRING *q)
{
	free(*q);
}

int main(void)
{
	STRING p = NULL;
	STRING str = "hello world";

	//printf("main::p = %p\n", p);
	get_mem(&p, strlen(str)+1 );
	//printf("main::p = %p\n", p);
	strcpy(p, str);

	puts(p);
	
	free_mem(&p);

	return 0;
}

#include <stdio.h>

#include "string_.h"

int main(void)
{
	char str1[100] = "abc";
	char *str2 = "hello world";
	char *p;

	p = strcpy_(str1, str2);
	puts(str1);
	puts(p);

	int res = strlen_(str2);
	printf("res = %d\n", res);

	p = strcat_(str1, str2);
	puts(str1);
	puts(p);

	res = strcmp_(str2, "hello world");
	printf("res = %d\n", res);

	p = strstr_(str2, "loa");
	//p = strchr_(str2, 'l');
	if(NULL == p)
	{
		printf("not found\n");
	}
	else
	{
		printf("p = %s\n", p);
	}

	return 0;
}

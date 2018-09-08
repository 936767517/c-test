#include <stdio.h>

int main(void)
{
	char str[20] = "computer";
	char *p = str;
	char *q = str + 1;

	for(; *p != '\0' && *q != '\0'; p += 2, q += 2)
	{
		printf("%c", *p);
	}
	printf("\n");

	return 0;
}

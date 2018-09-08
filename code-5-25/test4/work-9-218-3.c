#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[20] = "computer";
	char *p = str;
	int len = strlen(str);

	for(; p < str + len; p += 2)
	{
		printf("%c", *p);
	}
	printf("\n");

	return 0;
}

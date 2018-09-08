#include <stdio.h>
#include <string.h>

int main()
{
	char str[20] = "hello world";
	char *p = str;

	for(; p <= str+strlen(str); p += 2)
	{
		putchar(*p);
	}
	printf("\n");
	
	return 0;
}

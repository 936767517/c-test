#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[20] = "helloworld";
	char *s = "Jason";
	char *p;

	p = strcpy(str+5, s);

	puts(s);
	puts(str);
	puts(p);

	
	return 0;
}

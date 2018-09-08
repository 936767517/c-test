#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "hello\077world";
	char *s = "helloworld";

	printf("str = %d\n", sizeof(str));
	printf("str = %d\n", strlen(str) );
	printf("s = %d\n", sizeof(s));
	printf("s = %d\n", strlen(s) );
	
	return 0;
}

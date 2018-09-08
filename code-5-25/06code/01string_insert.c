#include <stdio.h>
#include <string.h>

void insert(char *dest, char *src, int n)
{
	char buff[100];

	strcpy(buff, dest + n);
	strcpy(dest + n, src);
	strcat(dest, buff);
}

int main(void)
{
	char str[30] = "helloworld";
	char *p = "jason";

	insert(str, p, 5);

	puts(str);
	
	return 0;
}

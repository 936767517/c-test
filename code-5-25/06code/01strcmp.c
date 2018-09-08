#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[20] = "Jason";
	char *s = "Jasona";

	int res = strcmp(s, str);
	printf("res = %d\n", res);
	
	return 0;
}

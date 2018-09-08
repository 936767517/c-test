#include <stdio.h>

int main(void)
{
	int i;
	char str[20] = "computer";
	char *p = str;

	for(i = 0; *(p+i) != '\0'; i++)
	{
		if(i % 2 == 0)
		{
			printf("%c", *(p + i));
		}
	}
	printf("\n");

	return 0;
}

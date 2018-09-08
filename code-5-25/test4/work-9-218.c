#include <stdio.h>

int main(void)
{
	int i;
	char str[20] = "computer";
	char *p = str;

	for(i = 0; *(p+i) != '\0'; i++)
	{
		printf("%c", *(p + i));
		i++;
		if(*(p+i) == '\0')
		{
			break;
		}
	}
	printf("\n");

	return 0;
}

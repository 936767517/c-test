#include <stdio.h>
#include <string.h>

int palindrome(char *string)
{
	char *head = string;
	char *tail = string + strlen(string) - 1;

	for(; head < tail; head++, tail--)
	{
		if(*head != *tail)
		{
			return 0;
		}
	}
	return 1;
}

int main(void)
{
	char str[100];

	scanf("%s", str);

	printf("%d\n", palindrome(str) );
	
	return 0;
}

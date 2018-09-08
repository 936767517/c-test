#include <stdio.h>

void strncat_(char dest[], char src[], int n)
{
	int i, j;

	// find end of @dest
	for(i = 0; dest[i] != '\0'; i++);

	// copy @src to @dest
	for(j = 0; src[j] != '\0' && j < n; j++, i++)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';
}

int main(void)
{
	char str_a[100];
	char str_b[20];

	scanf("%s %s", str_a, str_b);

	strncat_(str_a, str_b, 5);

	printf("str = %s\n", str_a);
	
	return 0;
}

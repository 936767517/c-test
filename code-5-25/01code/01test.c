#include <stdio.h>

// int main(int argc, char **argv)
int main(void)
{
	signed int a = -1;
	unsigned int b = 1;

	printf("a = %d %u\n", a, a);
	printf("a - b = %d\n", a-b);

	if(a > (signed int)b)
	{
		printf("Yes(a>b)\n");
	}
	else
	{
		printf("No(a<=b)\n");
	}

	return 0;
}

#include <stdio.h>
#include <string.h>

int main()
{
	char str[100] = {0};
	char *p = str;
	char c;
	int count = 0;

	scanf("%s", str);
	getchar();
	scanf("%c", &c);

	while(*p)
	{
		if(c == *p++)
			count++;
	}

	printf("count = %d\n", count);

	return 0;
}

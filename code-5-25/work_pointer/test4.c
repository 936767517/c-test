#include <stdio.h>
#include <string.h>

void swap(char *dest, int x, int y)
{
	char c = *(dest+x);
	*(dest+x) = *(dest+y);
	*(dest+y) = c;
}

int insert_(char *dest, int location, int value)
{
	int len = strlen(dest)+2;

	for(; len > location; len--)
	{
		swap(dest, len, len-1);
	}

	*(dest+location) = value;

	return 0;
}

char *insert(char *dest)
{
	int i;
	char *p = dest;

	for(i = 1; (p+i) < (dest + strlen(dest)); i+=2)
	{
		insert_(dest, i, ' ');
	}
	return dest;
}

int main()
{
	char str[40] = {0};

	scanf("%s", str);

	insert(str);

	puts(str);
	
	return 0;
}

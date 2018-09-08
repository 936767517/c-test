#include <stdio.h>
#include <string.h>

char *strmcopy(char *str, char *arr, int location)
{
	char *p;
	char *q = str;
	if(location > strlen(arr))
	{
		*str = '\0';
		return str;
	}

	arr += location-1;
	while(*q++ = *arr++);

	return str;
}

int main()
{
	char arr[20];
	char str[20];
	int m;

	scanf("%s", arr);
	scanf("%d", &m);

	strmcopy(str, arr, m);

	puts(str);

	
	return 0;
}

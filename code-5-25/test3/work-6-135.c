#include <stdio.h>

int find_max(char str[])
{
	int i;
	int max_pos = 0;

	for(i = 1; str[i] != '\0'; i++)
	{
		if(str[ max_pos ] < str[ i ])
		{
			max_pos = i;
		}
	}
	return max_pos;
}

int insert(char dest[], int pos, char src[], int len)
{
	int j = 0;
	int i = pos + 1;
	char buff[100];

	do
	{
		buff[j++] = dest[i];
	}while(dest[i++] != '\0');

	for(i = pos + 1, j = 0; j < len; j++, i++)
	{
		dest[i] = src[j];
	}

	j = 0;
	do
	{
		dest[i] = buff[j++];
	}while(dest[i++] != '\0');
}

int strlen_(char dest[])
{
	int i = 0; 

	while(dest[i++] != '\0');

	return i-1;
}

int insert_(char dest[], int pos, char src[], int len)
{
	int i = strlen_(dest);

	for(;i > pos; i--)
	{
		dest[ i + len ] = dest[i];
	}

	for(i = 0; i < len; i++)
	{
		dest[i + pos + 1] = src[i];
	}
}

int main(void)
{
	int res;
	char a[100];
	char b[] = "ab";
	int len_b = 2;

	scanf("%s", a);

	res = find_max(a);
	//printf("%d:%c\n", res, a[res]);

	insert_(a, res, b, len_b);

	printf("%s\n", a);
	
	return 0;
}

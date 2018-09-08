#include <stdio.h>

int find(char str[], int size, char ch)
{
	int i;

	for(i = 0; i < size; i++)
	{
		if(str[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

int find_half(char str[], int size, char ch)
{
	int left = 0;
	int right = size - 1;
	int mid;

	while(left < right)
	{
		mid = (left + right)/2;

		if(ch == str[mid])
		{
			return mid;
		}
		else if(ch < str[mid])
		{
			right = mid;
		}
		else // ch > str[mid]
		{
			left = mid;
		}
	}
	return -1;
}

int main(void)
{
	char letter[27] = "abcdefghijklmnopqrstuvwxyz";
	char ch;
	int res;

	scanf("%c", &ch);

	//res = find(letter, 26, ch);
	res = find_half(letter, 26, ch);
	if(res == -1)
	{
		printf("* *\n");
	}
	else
	{
		printf("%d : %c\n", res, letter[ res ] );
	}
	
	return 0;
}

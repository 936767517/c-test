#include <stdio.h>

int fun(char ch)
{
	if(ch >= 'a' && ch <= 'z')
	{
		return (ch - 'a' + 1);
	}
	else if(ch >= 'A' && ch <= 'Z')
	{
		return (ch - 'A' + 1);
	}
	else
	{
		return -1;
	}
}

int main(void)
{
	int res;
	char ch;

	while(1)
	{
		// get input data
		ch = getchar();
		if('\n' == ch || ' ' == ch || '\t' == ch)
		{
			continue;
		}
		if('0' == ch)
		{
			break;
		}

		// data => fun
		res = fun(ch);
		if(-1 == res)
		{
			printf("not a letter\n");
		}
		else
		{
			printf("%c is %d\n", ch, res);
		}
	}
	
	return 0;
}

#include <stdio.h>

int get_pos(char ch)
{
	if(ch >= 'a' && ch <= 'z')
	{
		return (ch - 'a');
	}
	else if(ch >= 'A' && ch <= 'Z')
	{
		return (ch - 'A');
	}
	else
	{
		return -1;
	}
}

int main(void)
{
	int i;
	char ch;
	int arr[26] = {};
	
	while((ch = getchar()) != '0')
	{
#if 0
		if('\n' == ch || ' ' == ch)
		{
			continue;
		}
#endif
		int res = get_pos(ch);
		if(res != -1)
		{
			arr[ res ]++;
		}
	}

	for(i = 0; i < 26; i++)
	{
		if(arr[i] != 0)
		{
			printf("%c:%d\n", 'a'+i, arr[i]);
		}
	}

	return 0;
}

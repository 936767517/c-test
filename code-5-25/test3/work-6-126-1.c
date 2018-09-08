#include <stdio.h>

int get_location(char ch)
{
	if(ch >= 'a' && ch <= 'z')
	{
		return (ch-'a');
	}
	else if(ch >= 'A' && ch <= 'Z')
	{
		return (ch-'A');
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
	int count[26] = {};

	// get input & count
	while(1)
	{
		scanf("%c", &ch);
		//printf("[%c]\n", ch);
		if('0' == ch)
		{
			break;
		}
	
		int res = get_location(ch);
		if(res != -1)
		{
			count[ res ]++;
		}
	}

	// print
	for(i = 0; i < 26; i++)
	{
		if(count[i] != 0)
		{
			printf("%c : %d\n", 'a'+i, count[i]);
		}
	}
	
	return 0;
}

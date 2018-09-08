#include <stdio.h>

int main(void)
{
	int i = 0;
	char str[1024] = {};
	int count = 0;
	int flag = 1;

	gets(str);

	while('\0' != str[i])
	{
		if(' ' == str[i])
		{
			flag = 1;
		}
		else if(1 == flag)
		{
			count++;
			flag = 0;
		}
		
		i++;
	}

	printf("count = %d\n", count);
	
	return 0;
}

#include <stdio.h>

int get_string_len(char str[])
{
	int i = 0;

	while(str[i++] != '\0') ;

	return i - 1;
}

void print_string(char string[])
{
	int i = 0;

	//while(1)
	// for(i = 0; string[i] != '\0'; i++)
	while(string[i] != '\0')
	{
		/*
		if(string[i] == '\0')
		{
			break;
		}
		*/
		printf("%c", string[i]);
		i++;
	}
	printf("\n");
}

void print_str(char str[])
{
	int i = 0;

	do
	{
		printf("%c", str[i]);
	}while(str[i++] != '\0');
	printf("\n");
}

int main(void)
{
	char str[20] = "helloworld";

	//printf("[%c]\n", '\0');

	scanf("%s", str);

	printf("%s\n", str);

	print_string(str);
	
	return 0;
}

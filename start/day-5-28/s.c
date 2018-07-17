#include<stdio.h>
int print_string(char str[])
{
	int i=0;
	while(1)
	{
		if(str[i]=='\0')
		{
			break;	
		}
		printf("%c ",str[i]);
		i++;
	}
	printf("\n");
}
int main(void)
{
	char str[20];
	scanf("%s",str);
	print_string(str);
	
	return 0;
}

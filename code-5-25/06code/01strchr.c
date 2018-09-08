#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[20] = "helloworld";
	char *s;

	s = strstr(str, "lo");
	//s = strchr(str, 'w');
	// printf("%s\n", s); // error
	if(NULL == s)
	{
		printf("not found\n");
	}
	else
	{
		printf("%s\n", s);
	}
	
	return 0;
}

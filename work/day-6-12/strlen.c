#include<stdio.h>
#include<string.h>
int main(void)
{
	char str[] ="helloworld";
	
	char *p=str;
	
	printf("str=%d\n",sizeof(str[0]));
	
	printf("str=%d\n",sizeof(*p));
	
	printf("p=%d\n",strlen(p));

	return 0;	
}

#include<stdio.h>
void str_cpy(char *s1,char *s2)
{
	while(*s1++=*s2++)
		;
	
}
int main(void)
{	
	char s1[]="hello world";
	char s2[]="good";
	str_cpy(s1,s2);
	printf("%s\n",s1);
	
	return 0;	
}

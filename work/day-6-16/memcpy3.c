#include<stdio.h>
#include<string.h>
int main(void)
{
	char s1[100]="hello world";
	char s2[100]="jason";
	memcpy(s1,s2,6);
	printf("%s\n",s1);
	
	return 0;	
}

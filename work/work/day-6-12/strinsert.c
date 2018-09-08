#include<stdio.h>
#include<string.h>
void insert (char *str,char *s,int n)
{
	char buff[100];
	strcpy(buff,str+n);
	strcpy(str+n,s);
	strcat(str,buff);
	
	
}
int main(void)
{
	char str[20]="helloworld";
	char s[6]="jason";

	insert (str,s,5);
	printf("%s\n",str);

	return 0;	
}

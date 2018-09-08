#include<stdio.h>
#include<string.h>
void insert(char *string)
{
	int len=strlen(string);
	char *p=string+2*len;
	char *q=string+len;
	while((q-string)>=0&&(p-string)!=0)
	{
		*p=*q;	
	
		*(p-1)=' ';
		
		p-=2;
		q--;
	}
	
}
int main(void)
{
	char s[100]={};
	scanf("%s",s);
	printf("%s\n",s);
	insert(s);
	printf("%s\n",s);
	return 0;	
}

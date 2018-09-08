#include<stdio.h>
#include"strfun.h"
int str_len (char *s)
{
	int i=0;
	do{
		i++;
	}
	while(s[i]!='\0');
	return i-1;
}
int str_cat(char *dest,char *sor)
{
	int i=0;
	int len=str_len(dest);
	do
	{
		dest[len+i]=sor[i];
	}while(sor[i++]!='\0');
	
}
int str_str(char *s1,char *s2)
{
	char *p=s1;
	char *q=s2;
	while(*s1!='\0')
	{
	for(;q!='\0'&&*q==*p;q++,p++)
		if(*q=='\0')
			return (char*)s1;
		s1++;
	}
	return NULL;
}

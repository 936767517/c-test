#include<stdio.h>
#include<string.h>
int* atoi(char *str)
{
	int sum=0;
	int flag =1;
	if('-'==*str)
	{
		str++;
		flag=-1;
	}
	while(*str!='\0')
	{
		sum=sum*10+(*str-'0');
		str++;
		
	}
	return (sum*flag);
}
char itoa(int num,char *str)
{
	if(num<0)
	{
		*str = '-';
		*(str+1)='\0';
		num*=-1;
	}
	if(num/10!=0)
	{
		itoa(num/10,str);	
	}
	for(;*str!='\0';str++);
	
		*str=num%10+'0';
		*(str+1)='\0';
}
float atof(char *str)
{
	int sum=0;
	int base = 0;
	int flag =1;
	if(*str=='-')
	{
		str++;
		flag=-1;
	}
	while(*str!='\0')
	{
		if(*str!='.')
		{
			sm=sum*10+(*str-'0');
			base *= 10;
		}
		else
		{
			base=1;	
		}
		str++;
		
	}
	if(0==base)
	{
		base=1;	
	}
	return (float)sum/base *flag;
}

int main(void)
{
	char str[100]={};
	//int num=atoi(str);
	int num = 314524;
	itoa(num,str);
	printf("str=%s\n",str);
	return 0;	
}

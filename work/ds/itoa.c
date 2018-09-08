#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	int num=1234;
	int count=0;
	int n;
	int i=0;
	int *l=NULL;
	char s[100]={};
	while(num!=0)
	{
		l=(int *)realloc(l,sizeof(*l)*(count+1));
		n=num%10;
		num=num/10;
		memcpy(l+count,&n,sizeof(int));
		count++;
	}
	while(count>0)
	{
		s[i]=*(l+count-1)+'0';
		s[i+1]='\0';
		count--;
		i++;
	}
	printf("s=%s\n",s);
	return 0;	
}

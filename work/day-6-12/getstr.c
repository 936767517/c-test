#include<stdio.h>
int main(void)
{
	char str[1024] ={};
	int count =0;
	int i=0;
	int flag=1;
	gets(str);
	puts(str);


	while(str[i]!='\0')
	{
		if(' '==str[i])
		{
			flag=1;
		}
		else if(flag==1)
		{
			count++;
			flag=0;
		}
		i++;
	
	}	

	printf("count=%d\n",count);
	return 0;	
}

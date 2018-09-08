#include<stdio.h>
int fun(char ch)
{
	if(ch >='A'&&ch <='Z')
	{
		return (ch  - 'A'+1);
	}
	else if(ch>='a'&&ch<='z')
	{
		return(ch - 'a'+1);
	}
	else
	{
		return -1;
	}
}
int main(void)
{
	char ch='a';
	while(ch!='0')

	{
		scanf("%c",&ch);
	if('\n'==ch||' '==ch||'\t'==ch)
	{
		continue;
	}
		int res=fun(ch);
		if(res!=-1)
		{
			printf("%c=%d\n",ch,res);
		}
		else
		{
			printf("error");
		}
	}
	return 0;
}

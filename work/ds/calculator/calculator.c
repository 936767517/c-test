#include <stdio.h>
#include "stack.h"
int main(void)
{
	int val=0;
	int flag=1;
	int oper;
	char *str="12+3*(6-2)";
	char *p=str;
	STACK number,operator;

	number=stack_create(50);
	if(NULL==number)
	{
		return -1;	
	}
	operator=stack_create(50);
	if(NULL==operator)
	{
		stack_dispose(number);
		return -2;
	}
	while(*str!='\0')
	{
		if(*str>='0'&&*str<='9')
		{
			val=val*10+(*str-'0');
			flag=1;
		}
		else
		{
			if(flag==1)
			{
				stack_push(number,&val);
				val=0;
				flag=0;
			}
			if(*str==')')
			{
				deal_bracket(number,operator);	
			}
			else
			{
				deal_oper(number,operator,*str);	
				
			}
		}
		str++;
	}
	if(flag==1)
	{
		stack_push(number,&val);	
	}
	while(!stack_is_empty(operator))
	{
		stack_top_and_pop(operator,&oper);
		compute(number,oper);
	}
	return 0;	
}

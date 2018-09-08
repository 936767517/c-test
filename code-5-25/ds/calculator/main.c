#include <stdio.h>

#include "stack.h"

int compute(STACK number, int oper)
{
	int n1, n2;
	int res;

	stack_top_and_pop(number, &n2);
	stack_top_and_pop(number, &n1);

	switch(oper)
	{
		case '+': res = n1 + n2; break;
		case '-': res = n1 - n2; break;
		case '*': res = n1 * n2; break;
		case '/': res = n1 / n2; break;
	}
	stack_push(number, &res);
	return 0;
}

int deal_bracket(STACK number, STACK operator)
{
	int oper;

	stack_top(operator, &oper);
	while(oper != '(')
	{
		stack_top_and_pop(operator, &oper);
		compute(number, oper);
		stack_top(operator, &oper);
	}
	stack_pop(operator);
	return 0;
}

int getnum(int op)
{
	switch(op)
	{
		case '(': return 0;
		case '-':
		case '+': return 1;
		case '*':
		case '/': return 2;
	}
}

int deal_oper(STACK number, STACK operator, int oper)
{
	if(oper == '(')
	{	
		stack_push(operator, &oper);
		return 0;
	}
	if(stack_is_empty(operator))
	{
		stack_push(operator, &oper);
		return 0;
	}
	int top;
	stack_top(operator, &top);

	if(getnum(top) < getnum(oper))
	{
		stack_push(operator, &oper);
		return 0;
	}

	while(getnum(top) >= getnum(oper))
	{
		stack_top_and_pop(operator, &top);
		compute(number, top);
		if(stack_is_empty(operator))
			break;
		stack_top(operator, &top);
	}
	stack_push(operator, &oper);
	return 0;
}

int main(void)
{
	int value = 0;
	int flag = 1;
	int oper;
	//char *str = "12+3*(6-2*(2+3))-2*5+12";
	char *str = "(3+2)*(3*2)*";
	char *p = str;
	STACK number, operator;

	number = stack_create(50);
	if(NULL == number)
		return -1;
	operator = stack_create(50);
	if(NULL == operator)
	{
		stack_dispose(number);
		return -2;
	}

	while(*str != '\0')
	{
		if(*str >= '0' && *str <= '9')
		{
			value = value * 10 + (*str-'0');
			flag = 1;
		}
		else // + - * / ( ) 
		{
			if(flag == 1)
			{
				stack_push(number, &value);
				value = 0;
				flag = 0;
			}
			if(*str == ')')
			{
				deal_bracket(number, operator);
			}
			else // + - * / (
			{
				deal_oper(number, operator, *str);
			}
		}
		
		str++;
	}
	if(flag == 1)
	{
		stack_push(number, &value);
	}

	while(!stack_is_empty(operator))
	{
		stack_top_and_pop(operator, &oper);
		compute(number, oper);
	}
	stack_top(operator,&oper);
	printf("[%c]\n",(char)oper);
	printf("%s=%d\n", p, number->data[number->top]);
	
	stack_dispose(number);
	stack_dispose(operator);

	return 0;
}

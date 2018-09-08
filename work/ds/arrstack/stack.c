#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack.h"
STACK stack_create(int size)
{
	STACK l=(STACK)malloc(sizeof(*l));
	if(l==NULL)
	{
		return NULL;	
	}
	l->data=(stack_type*)malloc(sizeof(stack_type)*size);
	if(l->data==NULL)
	{
		free(l);
		return NULL;
	}
	l->capacity=size;
	l->top=-1;
	return l;
}

void stack_dispose(STACK l)
{
	free(l->data);
	free(l);
}

int stack_is_full(STACK l)
{
	return (l->top==l->capacity-1);	
}
int stack_is_empty(STACK l)
{
	return (l->top==-1);	
}
int stack_push(STACK l,stack_type *data)
{
	if(stack_is_full(l))
	{
		return -1;	
	}
	memcpy(l->data+l->top+1,data,sizeof(stack_type));
	l->top++;
	return 0;
}
int stack_pop(STACK l)
{
	if(stack_is_empty(l))
	{
		return -1;	
	}
	l->top--;
	return 0;
}
int stack_top(STACK l,stack_type *data)
{
	if(stack_is_empty(l))
	{
		return -1;	
	}
	memcpy(data,l->data+l->top,sizeof(stack_type));
	return 0;
}

int stack_top_and_pop(STACK l,stack_type *data)
{
	if(0==stack_top(l,data))
	{
		return stack_pop(l);	
	}
	return -1;
}

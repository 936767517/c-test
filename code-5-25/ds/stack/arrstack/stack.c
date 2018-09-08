#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

STACK stack_create(int size)
{
	STACK head = (STACK)malloc(sizeof(*head));
	if(NULL == head)
	{
		return NULL;
	}
	head->data = (stack_type *)malloc(size * sizeof(stack_type));
	if(NULL == head->data)
	{
		free(head);
		return NULL;
	}
	head->capacity = size;
	head->top = -1;

	return head;
}

int stack_is_empty(STACK l)
{
	return -1 == l->top;
}

int stack_is_full(STACK l)
{
	return l->top+1 == l->capacity;
}

void stack_make_empty(STACK l)
{
	l->top = -1;
}

int stack_push(STACK l, const stack_type *data)
{
	if(stack_is_full(l))
		return -1;

	//l->data[l->top+1] = *data;
	memcpy(l->data + l->top + 1, data, sizeof(stack_type));
	l->top++;
	return 0;
}

int stack_pop(STACK l)
{
	if(stack_is_empty(l))
		return -1;
	l->top--;
	return 0;
}

int stack_top(STACK l, stack_type *data)
{
	if(stack_is_empty(l))
		return -1;
	memcpy(data, l->data+l->top, sizeof(stack_type));
	return 0;
}

int stack_top_and_pop(STACK l, stack_type *data)
{
	if(0 == stack_top(l, data))
		return stack_pop(l);
	return -1;
}

void stack_dispose(STACK l)
{
	free(l->data);
	free(l);
}

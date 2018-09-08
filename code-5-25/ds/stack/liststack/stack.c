#include <stdio.h>

#include "stack.h"

STACK stack_create(int size)
{
	return list_create(size);
}

int stack_is_empty(STACK l)
{
	return list_is_empty(l);
}

int stack_push(STACK l, const void *data)
{
	return list_insert(l, data, HEADINSERT);
}

static int match(const void *data, const void *key)
{
	return 0;
}

int stack_pop(STACK l)
{
	return list_delete(l, (void *)0, match);
}

void *stack_top(STACK l)
{
	return list_find(l, (void *)0, match);
}

int stack_top_and_pop(STACK l, void *data)
{
	return list_fetch(l, (void *)0, match, data);
}

void stack_dispose(STACK l)
{
	list_dispose(l);
}

#ifndef _STACK_H__
#define _STACK_H__

#include "xylist.h"

typedef LIST STACK;

STACK stack_create(int size);
int stack_is_empty(STACK l);
int stack_push(STACK l, const void *data);
int stack_pop(STACK l);
void *stack_top(STACK l);
int stack_top_and_pop(STACK l, void *data);
void stack_dispose(STACK l);

#endif

#ifndef _STACK_H_
#define _STACK_H_
struct stack_node;
typedef struct stack_node *STACK;
typedef int stack_type;
struct stack_node{
	int top;
	int capacity;
	stack_type *data;
	};
STACK stack_create(int size);
int stack_is_full(STACK l);
int stack_is_empty(STACK l);

int stack_push(STACK l,stack_type *data);
int stack_pop(STACK l);
int stack_top(STACK l,stack_type *data);
int stack_top_and_pop(STACK l,stack_type *data);
void stack_dispose(STACK l);

#endif

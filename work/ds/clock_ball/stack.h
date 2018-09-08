#ifndef _STACK_H__
#define _STACK_H__

typedef int stack_type;

struct stack_node;
typedef struct stack_node *STACK;

STACK stack_create(int size);
int stack_is_empty(STACK l);
int stack_is_full(STACK l);
int stack_push(STACK l, const stack_type *data);
int stack_pop(STACK l);
int stack_top(STACK l, stack_type *data);
int stack_top_and_pop(STACK l, stack_type *data);
void stack_make_empty(STACK l);
void stack_dispose(STACK l);

struct stack_node {
	stack_type *data; // 栈空间
	int capacity; // 栈容量
	int top; // 栈顶下标
};

#endif

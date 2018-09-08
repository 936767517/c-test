#include <stdio.h>

#include "stack.h"

int main(void)
{
	int i;
	stack_type data;
	stack_type arr[] = {3,1,2,5,7,9,6,8};
	STACK head = NULL;

	head = stack_create(20);
	if(NULL == head)
	{
		return -1;
	}
	
	for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		stack_push(head, arr+i);
	}
	stack_pop(head);
	stack_top_and_pop(head, &data);
	printf("data = %d\n", data);
	stack_top(head, &data);
	printf("data = %d\n", data);

	stack_dispose(head);

	return 0;
}

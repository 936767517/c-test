#include <stdio.h>

#include "list.h"

int main(void)
{
	int i;
	Type id = 17;
	PtrNode p;
	Type arr[] = {3,1,2,5,7,9,6,8};
	LIST handle = NULL;

	handle = list_create();
	if(NULL == handle)
	{
		return -1;
	}

	for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		//list_insert_head(handle, arr+i);
		list_insert_tail(handle, arr+i);
	}
	p = list_find(handle, &id);
	if(NULL == p)
	{
		printf("not found\n");
	}
	else
	{
		printf("p->data = %d\n", p->data);
	}
	p = list_find_prev(handle, &id);
	if(list_is_last(handle, p))
	{
		printf("not found\n");
	}
	else
	{
		printf("p->data = %d\n", p->data);
	}

	list_delete(handle, &id);

	list_reverse(handle);

	list_display(handle);
	list_dispose(handle);
	
	return 0;
}

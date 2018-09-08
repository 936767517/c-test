#include <stdio.h>

#include "queue.h"

int main(void)
{
	int i;
	queue_type data;
	queue_type arr[] = {3,1,2,5,7,9,6,8};
	QUEUE head = NULL;

	head = queue_create(12);
	if(NULL == head)
	{
		return -1;
	}

	for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		queue_en(head, arr+i);
	}
	queue_front_and_de(head, &data);
	printf("data = %d\n", data);
	queue_de(head);
	queue_front(head, &data);
	printf("data = %d\n", data);

	queue_dispose(head);
	
	return 0;
}

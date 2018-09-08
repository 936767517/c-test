#include<stdio.h>
#include"queue.h"
int main(void)
{
	int arr[]={3,1,2,5,7,9,6,8};
	int i;
	QUEUE head=NULL;
	head=queue_create(12);
	for(i=0;i<sizeof(arr)/sizeof(*arr);i++)
	{
		queue_en(head,arr+i);	
	}
	queue_de(head);
	queue_front(head,&i);
	printf("i=%d\n",i);
	queue_dispose(head);
	return 0;	
}

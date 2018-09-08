#include<stdio.h>
#include"list.h"
void print_data(LIST p)
{
	printf("%d ",p->data);	
}
int main(void)

{
	LIST handle=list_creat();
	int arr[]={3,2,1,5,4,6,7,8};
	int key=8;
	int i;
	for(i=0;i<sizeof(arr)/sizeof(*arr);i++)
	{
		int res=list_insert(handle,arr+i);	
	}
	LIST p=list_find(handle,&key);
	if(p==NULL)
	{
		printf("not found");	
	}
	else{
	print_data(p);}
	printf("===========\n");
	//list_delete(handle,&key);
	list_display(handle,&print_data);
	printf("\n");
	int res=list_dao(handle);
	printf("res=%d\n",res);
	printf("l->next=%d\n",handle->next->data);
	list_display(handle,&print_data);
	printf("\n");
	list_destroy(handle);
	return 0;	
}

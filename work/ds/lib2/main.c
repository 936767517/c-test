#include<stdio.h>
#include"list.h"
struct stu_info{
	int id;
	char name[25];
	};
void print_data(void* data)
{
	struct stu_info* p=data;
	printf("%d %s\n",p->id,p->name);
}
int id_cmp(void *data,void *key)
{
	struct stu_info* p=data;
	int *q=key;
	return (p->id-*q);
}
int main(void)
{
	int arr[]={3,1,2,5,7,9,6,8};
	int i;
	int id=5;
	LIST res;
	struct stu_info tmp;
	struct stu_info* stup;
	HEAD head=NULL;
	head=list_create(sizeof(tmp));
	if(head==NULL)
	{
		return -1;	
	}
	for(i=0;i<sizeof(arr)/sizeof(*arr);i++)
	{
		tmp.id=arr[i];
		snprintf(tmp.name,25,"student%d",*(arr+i));
		list_insert(head,&tmp,HEADINSERT);
	}
	res=list_find(head,&id,id_cmp);
	print_data(res->data);
	list_delete(head,&id,id_cmp);
	list_display(head,print_data);
	return 0;	
}

#include<stdio.h>
#include"darr.h"
struct stu_info{
	int id;
	char name[25];
	};
int id_cmp(void *data,void *key)
{
	struct stu_info* p=data;
	int *q=key;
	return (p->id - *q);
}
int name_cmp(void *data,void *key)
{
	struct stu_info* p=data;
	char *name=key;
	return strcmp(p->name,name);
}
void print_data(void *data)
{
	struct stu_info* p=(struct stu_info*)data;
	printf("%d %s\n",p->id,p->name);
}
int main(void)
{
	struct stu_info stup;
	int arr[]={3,1,2,5,7,9,6,8};
	int i;
	int id=5;
	DARR head=NULL;
	head=darr_create(sizeof(stup));
	if(head==NULL)
	{
		return -1;
	}
	for(i=0;i<(sizeof(arr)/sizeof(*arr));i++)
	{
		stup.id=arr[i];
		snprintf(stup.name,25,"student%d",arr[i]);
		darr_insert(head,&stup);
	}
	struct stu_info* n=darr_find(head,&id,id_cmp);
	print_data(n);
	darr_delete(head,&id,id_cmp);
	darr_display(head,print_data);
	darr_dispose(head);
	return 0;	
}

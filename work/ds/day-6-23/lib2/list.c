#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

LIST list_create(int size)
{
	LIST l=(LIST)malloc(sizeof(*l));
	if(NULL==l)
	{
		return NULL;	
	}
	l->size=size;
	l->head.data=NULL;
	l->head.next=l->head;
	l->head.prev=l->head;
	return l;
}
int list_insert(LIST l, const void *data, int mode)
{
	PtrNode p=(PtrNode)malloc(*p);
	if(NULL==p)
	{
		return -1;		
	}
	p->data=malloc(l->size);
	if(NULL==p->data)
	{
		free(p);
		return -2;	
	}
	memcpy(p->data,data,l->size);
	if(mode==HEADINSERT)
	{
		p->next=l->head.next;
		p->prev=&l->head;
	}
	else if(mode==TAILINSERT)
	{
		p->next=&l->head;
		p->prev=l->head.prev;
	}
	else
	{
		free(p->data);
		free(p);
		return -3;	
	}
	p->next->prev=p;
	p->prev->next=p;
	return 0;
}
static PtrNode find(LIST l,const void *key,list_cmp *funp)
{
	PtrNode p=l->head.next;
	for(;p!=&l->head&&funp(p->data,key);p=p->next);
	return p;
}
void *list_find(LIST l, const void *key, list_cmp *funp)
{
	return find(l,key,funp)->data;
}

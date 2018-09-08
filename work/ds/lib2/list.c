#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
HEAD list_create(int size)
{
	HEAD l=(HEAD)malloc(sizeof(*l));
	if(NULL==l)
	{
		return NULL;	
	}
	l->size=size;
	l->head.data=NULL;
	l->head.next=&l->head;
	l->head.prev=&l->head;
	return l;
}
int list_insert(HEAD l,void *data,int mode)
{
	LIST p=(LIST)malloc(sizeof(*p));
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
		p->prev=l->head.prev;
		p->next=&l->head;
	}
	else
	{
		free(p->data);
		free(p);
		return -3;
	}
	p->prev->next=p;
	p->next->prev=p;
	return 0;
}
void *list_find(HEAD l,void *key,list_cmp funp)
{
	LIST p=l->head.next;
	for(;p!=&l->head&&funp(p->data,key);p=p->next);
	return p;
}
int list_delete(HEAD l,void *key,list_cmp *funp)
{
	LIST p=list_find(l,key,funp);
	if(p==&l->head)
	{
		return -1;	
	}
	p->prev->next=p->next;
	p->next->prev=p->prev;
	free(p->data);
	free(p);
	return 0;
}
void list_display(HEAD l,list_print *funp)
{
	LIST p=l->head.next;
	for(;p!=&l->head;p=p->next)
	{
		funp(p->data);	
	}

}
void list_dispose(HEAD l)
{
	LIST p=l->head.next;
	LIST q;
	for(;p!=&l->head;)
	{
		q=p;
		p=p->next;
		free(q);
	}
}

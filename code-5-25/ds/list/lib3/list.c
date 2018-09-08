#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

LIST list_create(int size)
{
	LIST l = (LIST)malloc(sizeof(*l));
	if(NULL == l)
	{
		return NULL;
	}
	l->size = size;
	l->head.prev = &l->head;
	l->head.next = &l->head;

	return l;
}

int list_insert(LIST l, const void *data, int mode)
{
	// create new data node 
	PtrNode cur = (PtrNode)malloc(sizeof(*cur)+l->size);
	if(NULL == cur)
	{
		return -1;
	}
	memcpy(cur->data, data, l->size);

	// insert new node
	if(HEADINSERT == mode)
	{
		cur->next = l->head.next;
		cur->prev = &l->head;
	}
	else if(TAILINSERT == mode)
	{
		cur->next = &l->head;
		cur->prev = l->head.prev;
	}
	else
	{
		free(cur);
		return -3;
	}

	cur->next->prev = cur;
	cur->prev->next = cur;
	return 0;
}

static PtrNode find(LIST l, const void *key, list_cmp *funp)
{
	PtrNode p = l->head.next;

	for(;p != &l->head && funp(p->data, key); p = p->next);

	return p;
}

void *list_find(LIST l, const void *key, list_cmp *funp)
{
	PtrNode p = find(l, key, funp);

	if(p == &l->head)
		return NULL;
	return p->data;
}

int list_delete(LIST l, const void *key, list_cmp *funp)
{
	PtrNode p = find(l, key, funp);
	if(p == &l->head)
	{
		return -1;
	}

	p->prev->next = p->next;
	p->next->prev = p->prev;
	
	free(p);
	return 0;
}

int list_fetch(LIST l, const void *key, list_cmp *funp, void *data)
{
	PtrNode p = find(l, key, funp);
	if(p == &l->head)
	{
		return -1;
	}
	memcpy(data, p->data, l->size);

	p->prev->next = p->next;
	p->next->prev = p->prev;
	
	free(p);
	return 0;
}

void list_display(LIST l, list_print *funp)
{
	PtrNode p = l->head.next;

	for(; p != &l->head; p = p->next)
	{
		funp(p->data);
	}
}

int list_is_empty(LIST l)
{
	return l->head.next == &l->head && l->head.prev == &l->head;
}

void list_dispose(LIST l)
{
	PtrNode p = l->head.prev;
	PtrNode q;

	while( p != &l->head )
	{
		q = p;
		p = p->prev;

		free(q);
	}
	free(l);
}





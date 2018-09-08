#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

LIST list_create(void)
{
	// 创建头结点
	LIST l = (LIST)malloc(sizeof(*l));
	if(NULL == l)
	{
		return NULL;
	}
	//l->data;
	l->next = TAIL(l);

	return l;
}

Position TAIL(LIST l)
{
	return NULL;
}

int list_is_empty(LIST l)
{
	return l->next == TAIL(l);
}

int list_is_last(LIST l, PtrNode p)
{
	return p->next == TAIL(l);
}

int list_insert(LIST l, Position prev, const Type *data)
{
	// 在@prev结点后插入一个新的结点
	PtrNode cur = (PtrNode)malloc(sizeof(*cur));
	if(NULL == cur)
	{
		return -1;
	}
	memcpy(&cur->data, data, sizeof(Type));

	cur->next = prev->next;
	prev->next = cur;

	return 0;
}

int list_insert_head(LIST l, const Type *data)
{
	// 首部插入
	list_insert(l, l, data);
}

int list_insert_tail(LIST l, const Type *data)
{
	// 尾部插入
	Position p = l;
	
	for(; p->next != TAIL(l); p = p->next);

	list_insert(l, p, data);
}

static int cmp(const Type *data, const Type *key)
{
	return (*data - *key);
}

PtrNode list_find(LIST l, const Type *key)
{
	Position p = l->next;

	for(; p != NULL && cmp(&p->data, key); p = p->next);

	return p;
}

PtrNode list_find_prev(LIST l, const Type *key)
{
	Position p = l;

	for(; p->next != NULL && cmp(&p->next->data, key); p = p->next);

	return p;
}

int list_delete(LIST l, const Type *key)
{
	Position p;
	p = list_find_prev(l, key);

	if(!list_is_last(l, p))
	{
		Position q = p->next;
		p->next = q->next;
		free(q);
		return 0;
	}
	return -1;
}

int list_reverse(LIST l)
{
	PtrNode p, q;
	p = l->next;
	l->next = NULL;

	while(p != NULL)
	{
		q = p;
		p = p->next;

		q->next = l->next;
		l->next = q;
	}
	return 0;
}

static void print_data(const Type *data)
{
	printf("%d ", *data);
}

void list_display(LIST l)
{
	Position p = l->next;

	for(; p != TAIL(l); p = p->next)
	{
		print_data(&p->data);
	}
	printf("\n");
}

void list_dispose(LIST l)
{
	Position p = l->next;
	Position q;

	while(p != TAIL(l))
	{
		q = p;
		p = p->next;

		free(q);
	}
	free(l);
}











#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "darr.h"

DARR darr_create(int size)
{
	// struct node *l ;
	DARR l = (DARR)malloc(sizeof(*l));
	if(NULL == l)
	{
		return NULL;
	}
	l->data = NULL;
	l->num = 0;
	l->size = size;

	return l;
}

int darr_insert(DARR l, const void *data)
{
	void *tmp = l->data;
	// alloc new mem for @data
	l->data = realloc(tmp, (l->num+1)*l->size );
	if(NULL == l->data)
	{
		l->data = tmp;
		return -1;
	}
	
	// store @data at end of @l->data
	memcpy(l->data + l->num*l->size, data, l->size);
	l->num++;
	return 0;
}

int darr_delete(DARR l, const void *key, darr_cmp *funp)
{
	int i;
	char *p = l->data;

	for(i = 0; i < l->num && funp(p, key); i++, p += l->size);

	if(i < l->num)
	{
		memmove(p, p + l->size, l->size*(l->num - i - 1));
		p = l->data;
		l->data = realloc(p, l->size*(l->num-1));
		if(NULL == l->data)
		{
			l->data = p;
			return -2;
		}
		l->num--;
		return 0;
	}
	return -1;
}

void *darr_find(DARR l, const void *key, darr_cmp *funp)
{
	int i;
	char *p = l->data;

	for(i = 0; i < l->num; i++, p += l->size)
	{
		if(0 == funp(p, key))
		{
			return p;
		}
	}
	return NULL;
}

//void darr_display(DARR l, void (*funp)(const void *))
void darr_display(DARR l, darr_print *funp)
{
	int i;
	char *p = l->data;

	for(i = 0; i < l->num; i++)
	{
		//p = l->data + i*l->size;
		funp(p);
		p += l->size;
	}
}

void darr_dispose(DARR l)
{
	free(l->data);
	free(l);
}








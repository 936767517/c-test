#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"darr.h"

DARR darr_create(int size)
{
	DARR l=(DARR)malloc(sizeof(*l));
	if(l==NULL)
	{
		return NULL;	
	}
	l->size=size;
	l->num=0;
	l->data=NULL;
}
int darr_insert(DARR l,void *data)
{
	void* p=l->data;
	l->data=realloc(p,l->size*(l->num+1));
	if(l->data==NULL)
	{
		l->data =p;
		return -1;	
	}
	memcpy(l->data+l->size*l->num,data,l->size);
	l->num++;
	return 0;
}
void darr_display(DARR l,darr_print * funp)
{
	char* p=l->data;
	int i;
	for(i=0;i<l->num;i++)
	{
		funp(p);
		p=p+l->size;
	}
}
void * darr_find(DARR l,void* data,darr_cmp funp)
{
	void *p=l->data;
	int i;
	for(i=0;i<l->num;i++)
	{
		if(funp(p,data)==0)
		{
			return p;	
		}
		p=p+l->size;
	}
	return NULL;
}
int  darr_delete(DARR l,void *data,darr_cmp funp)
{
	char *p=l->data;
	int i;
	for(i=0;i<l->num;i++)
	{
		if(funp(p,data)==0)
		{
			memmove(p,p+l->size,l->size*(l->num-i-1));
			p=l->data;
			l->data=realloc(l->data,l->size*l->num-1);
			if(NULL==l->data)
			{
				l->data=p;
				return -2;
			}
			l->num--;
			return 0;
		}
		p=p+l->size;
	}
	return -1;
}
void darr_dispose(DARR l)
{
	free(l->data);
	free(l);
}


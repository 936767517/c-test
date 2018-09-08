#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
LIST list_creat(void)
{
	LIST l=(LIST)malloc(sizeof(*l));
	if(NULL==l)
	{
		return NULL;	
	}
	l->next=TAIL(l);
	return l;
}
LIST TAIL(LIST l)
{
	return l;	
}
int list_insert(LIST l,Type* data)
{
	LIST p =(LIST)malloc(sizeof(*l));
	if(NULL==p)
	{
		return -1;	
	}
	//memcpy(&p->data,data,sizeof(Type));
	p->data=*data;
	p->next=l->next;
	l->next=p;
	return 0;
}
void list_display(LIST l,FUNP* funp)
{
	LIST p=l->next;
	for(;p!=TAIL(l);p=p->next)
	{
		funp(p);		
	}
}

LIST list_find(LIST l,Type * key)
{
	LIST p=l;
	for(;p!=TAIL(l);p=p->next)
	{
		if(p->data==*key)
		{
			return p;	
		}
	}
	return NULL;
}
int list_delete(LIST l,Type* key)
{
	LIST p=l;
	for(;p->next!=TAIL(l);p=p->next)
	{
		if(p->next->data==*key)
		{
			LIST q=p->next;
			p->next=q->next;
			free(q);
			return 0;
		}
	}
	return -1;
}
int  list_dao(LIST l)
{
	LIST p=l->next;
	LIST q;
	l->next=NULL;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		q->next=l->next;
		l->next=q;
		printf("%d ",l->next->data);
	}
	printf("\n");
	return 0;
}
int list_destroy(LIST l)
{
	LIST p=l->next;
	LIST q;
	while(p!=TAIL(l))
	{
		q=p;
		p=p->next;
		free(q);
	}
	free(l);
}






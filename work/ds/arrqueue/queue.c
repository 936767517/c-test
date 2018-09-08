#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"queue.h"
QUEUE queue_create(int size)
{
	QUEUE l=(QUEUE)malloc(sizeof(*l));
	if(l==NULL)
	{
		return NULL;	
	}
	l->data=(queue_type*)malloc(size*sizeof(queue_type));
	if(l->data==NULL)
	{
		return NULL;	
	}
	l->capacity=size;
	l->front=0;
	l->rear=l->front-1;
	l->num=0;
	return l;
}
int queue_is_empty(QUEUE l)
{
	return (l->num==0);	
}
int queue_is_full(QUEUE l)
{
	return (l->num==l->capacity);	
}
void queue_make_empty(QUEUE l)
{
	l->num=0;
	l->front=0;
	l->rear=l->front-1;
}
int repeat(QUEUE l,int num)
{
	num=num++%l->capacity;
	return num;
}
int queue_en(QUEUE l,queue_type *data)
{
	if(queue_is_full(l))
	{
		return -1;	
	}
	l->rear=repeat(l,l->rear);
	memcpy(l->data+l->rear,data,sizeof(queue_type));
	l->num++;
	return 0;
}
int queue_front(QUEUE l,queue_type *data)
{
	if(queue_is_empty(l))
	{
		return -1;	
	}
	memcpy(data,l->data+l->front,sizeof(queue_type));
	return 0;
}
int queue_de(QUEUE l)
{
	if(queue_is_empty(l))
	{
		return -1;	
	}
	l->front=repeat(l,l->front);
	l->num--;
	return 0;
}
void queue_dispose(QUEUE l)
{
	free(l->data);
	free(l);
}

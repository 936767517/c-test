#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

QUEUE queue_create(int size)
{
	QUEUE l = (QUEUE)malloc(sizeof(*l));
	if(NULL == l)
	{
		return NULL;
	}
	l->data = (queue_type *)malloc(size * sizeof(queue_type));
	if(NULL == l->data)
	{
		free(l);
		return NULL;
	}
	
	l->capacity = size;
	queue_make_empty(l);

	return l;
}

int queue_is_empty(QUEUE l)
{
	return 0 == l->size;
}

int queue_is_full(QUEUE l)
{
	return l->size == l->capacity;
}

void queue_make_empty(QUEUE l)
{
	l->size = 0;
	l->front = 0; 
	l->rear = l->front - 1;
}

int repeat(QUEUE l, int value)
{
	if(++value == l->capacity)
		value = 0;

	return value;
}

int queue_en(QUEUE l, const queue_type *data)
{
	if(queue_is_full(l))
		return -1;

	l->rear = repeat(l, l->rear);
	//l->data[l->rear] = *data;
	memcpy(l->data+l->rear, data, sizeof(queue_type));
	l->size++;
	return 0;
}

int queue_de(QUEUE l)
{
	if(queue_is_empty(l))
		return -1;
	
	l->front = repeat(l, l->front);
	l->size--;
	return 0;
}

int queue_front(QUEUE l, queue_type *data)
{
	if(queue_is_empty(l))
		return -1;
	
	memcpy(data, l->data+l->front, sizeof(queue_type));
	return 0;
}

int queue_front_and_de(QUEUE l, queue_type *data)
{
	if(0 == queue_front(l, data))
		return queue_de(l);
	return -1;
}

void queue_dispose(QUEUE l)
{
	free(l->data);
	free(l);
}











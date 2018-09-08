#include <stdio.h>

#include "queue.h"

QUEUE queue_create(int size)
{
	return list_create(size);
}

int queue_is_empty(QUEUE l)
{
	return list_is_empty(l);
}

int queue_en(QUEUE l, const void *data)
{
	return list_insert(l, data, TAILINSERT);
}

static int cmp(const void *data, const void *key)
{
	return 0;
}

int queue_de(QUEUE l)
{
	return list_delete(l, (void *)0, cmp);
}

void *queue_front(QUEUE l)
{
	return list_find(l, (void *)0, cmp);
}

int queue_front_and_de(QUEUE l, void *data)
{
	return list_fetch(l, (void *)0, cmp, data);
}

void queue_dispose(QUEUE l)
{
	list_dispose(l);
}

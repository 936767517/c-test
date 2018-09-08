#ifndef _QUEUE_H__
#define _QUEUE_H__

#include "list.h"

typedef LIST QUEUE;

QUEUE queue_create(int size);
int queue_is_empty(QUEUE l);
int queue_en(QUEUE l, const void *data);
int queue_de(QUEUE l);
void *queue_front(QUEUE l);
int queue_front_and_de(QUEUE l, void *data);
void queue_dispose(QUEUE l);

#endif

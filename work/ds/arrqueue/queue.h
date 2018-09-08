#ifndef _QUEUE_H_
#define _QUEUE_H_
typedef int queue_type;
struct node;
typedef struct node*  QUEUE;
QUEUE queue_create(int size);
int queue_is_empty(QUEUE l);
int queue_is_full(QUEUE l);
int queue_en(QUEUE l,queue_type *data);
int queue_front(QUEUE l,queue_type *data);
int queue_de(QUEUE l);
void queue_dispose(QUEUE l);
struct node{
	queue_type *data;
	int capacity;
	int num;
	int front;
	int rear;
	};


#endif

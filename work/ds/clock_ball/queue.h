#ifndef _QUEUE_H__
#define _QUEUE_H__

typedef int queue_type;

struct queue_node;
typedef struct queue_node *QUEUE;

QUEUE queue_create(int size);
int queue_is_empty(QUEUE l);
int queue_is_full(QUEUE l);
void queue_make_empty(QUEUE l);
int queue_en(QUEUE l, const queue_type *data);
int queue_de(QUEUE l);
int queue_front(QUEUE l, queue_type *data);
int queue_front_and_de(QUEUE l, queue_type *data);
void queue_dispose(QUEUE l);

struct queue_node {
	queue_type *data; // 队列
	int capacity; // 队列的总容量
	int size; // 队列现有容量
	int front; // 队头下标
	int rear; // 队尾下标
};

#endif

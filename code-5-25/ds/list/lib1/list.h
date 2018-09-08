#ifndef _LIST__H_
#define _LIST__H_

typedef int Type;

struct list_node;
typedef struct list_node *LIST;
typedef struct list_node *Position;
typedef struct list_node *PtrNode;

LIST list_create(void);
Position TAIL(LIST l);
int list_is_empty(LIST l);
int list_is_last(LIST l, PtrNode p);
int list_insert(LIST l, Position prev, const Type *data);
int list_insert_head(LIST l, const Type *data);
int list_insert_tail(LIST l, const Type *data);
PtrNode list_find(LIST l, const Type *key);
PtrNode list_find_prev(LIST l, const Type *key);
int list_delete(LIST l, const Type *key);
int list_reverse(LIST l);
void list_display(LIST l);
void list_dispose(LIST l);


struct list_node {
	Type data;
	struct list_node *next;
};

#endif

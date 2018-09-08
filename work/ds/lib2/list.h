#ifndef _LIST_H_
#define _LIST_H_
enum {HEADINSERT,TAILINSERT};
typedef void list_print(void *data);
typedef int list_cmp(void *data,void *key);
struct list_node;
typedef struct head_node *HEAD;
typedef struct list_node *LIST;
//create
HEAD list_create(int size);
//insert
int list_insert(HEAD l,void* data,int mode);
//find
void *list_find(HEAD l,void* key,list_cmp funp);
//delete
int list_delete(HEAD l,void *key,list_cmp funp);
//dispaly
void list_display(HEAD l,list_print* funp );
//dispose
void list_dispose(HEAD l);
struct list_node{
	void *data;
	struct list_node *prev;
	struct list_node *next;
	};
struct head_node{
	int size;
	struct list_node head;
	};
#endif

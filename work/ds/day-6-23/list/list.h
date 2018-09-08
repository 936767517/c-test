#ifndef  _LIST_H_
#define _LIST_H_
typedef int Type;
struct node;
typedef struct node *LIST;
typedef void FUNP(LIST p); 
LIST list_creat(void);
LIST TAIL(LIST l);
int list_insert(LIST l,Type* data);

void list_display(LIST l,FUNP* funp);
LIST list_find(LIST l,Type * key);
int list_delete(LIST l,Type* key);
int list_destroy(LIST l);
int  list_dao(LIST l);
struct node {
	Type data;
	LIST next;
	};
#endif

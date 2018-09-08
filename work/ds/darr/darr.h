#ifndef  _DARR_H_
#define  _DARR_H_
struct node;
typedef struct node* DARR;
typedef void darr_print(void* data);
typedef int darr_cmp(void * data,void*key);
//创建
DARR darr_create(int size);
int darr_insert(DARR l,void *data);
void* darr_find(DARR l,void *data,darr_cmp funp);
int  darr_delete(DARR l,void *data,darr_cmp funp);

void darr_display(DARR l,darr_print funp);
void darr_dispose(DARR l);
struct node{
	int size;
	int num;
	char *data;
	};


#endif

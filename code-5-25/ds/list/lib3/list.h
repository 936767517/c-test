#ifndef _LIST_H__
#define _LIST_H__

enum insert_mode {HEADINSERT, TAILINSERT};

typedef void list_print(const void *data);
typedef int list_cmp(const void *data, const void *key);
// T:0 F:!0

struct head_node;
struct list_node;
typedef struct head_node *LIST;
typedef struct list_node *PtrNode;

// 创建 插入 删除 提取 查找 遍历 销毁 
LIST list_create(int size);
int list_is_empty(LIST l);
int list_insert(LIST l, const void *data, int mode);
void *list_find(LIST l, const void *key, list_cmp *funp);
int list_delete(LIST l, const void *key, list_cmp *funp);
int list_fetch(LIST l, const void *key, list_cmp *funp, void *data);
void list_display(LIST l, list_print *funp);
void list_dispose(LIST l);

// 数据结点
struct list_node {
	struct list_node *prev;
	struct list_node *next;
	char data[0];
};

// 头结点
struct head_node {
	int size;
	struct list_node head;
};

#endif

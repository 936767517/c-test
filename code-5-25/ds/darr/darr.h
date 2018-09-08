#ifndef _DARR_H__
#define _DARR_H__

typedef void darr_print(const void *data);
typedef int darr_cmp(const void *data, const void *key);
// 0:cmp !0:!cmp

struct node;
typedef struct node *DARR;

// 创建
DARR darr_create(int size);
// 插入
int darr_insert(DARR l, const void *data);
// 删除
int darr_delete(DARR l, const void *key, darr_cmp *funp);
// 查找
void *darr_find(DARR l, const void *key, darr_cmp *funp);
// 销毁
void darr_dispose(DARR l);
// 遍历
//void darr_display(DARR l, void (*funp)(const void *));
void darr_display(DARR l, darr_print *funp);

struct node{
	char *data; // 存储数据
	int num; // 结点的个数
	int size; // 结点的字节数
};

#endif

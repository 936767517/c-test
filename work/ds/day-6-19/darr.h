#ifndef  __DARR_H__
#define  __DARR_H_
struct node{
		int num;
		int size;
		char* data;
	};
typedef struct node DARR;
//创建
void * arr_create(DARR *l,int size);
//插入
//删除
//寻找
//销毁
//遍历

#endif

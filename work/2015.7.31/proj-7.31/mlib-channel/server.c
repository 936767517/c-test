
/*
 *	-M          指定多播地址
 *	-P			指定测试用端口
 *	-F			前台调试运行
 *	-D			指定调试频道
 *	-H          显示帮助
 *
 * */
#include "medialib.h"
#include "./include/proto.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	struct mlib_chn_st *listptr;
	int listsize;
	int i;

	if(mlib_getchnlist(&listptr,&listsize) < 0)
	{
		syslog();
	}

	for(i = 0; i<listsize; i++)
	{
		printf("%s\n", listptr[i].desc);
	}


	exit(0);
}


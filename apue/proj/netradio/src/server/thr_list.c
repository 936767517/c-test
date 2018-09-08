#include<stdio.h>
#include<stdlib.h>
#include"thr_list.h"
static thread_list_work()
{
	struct mlib_chn_st *desc;
	mlib_getchnlist(&desc,)
}
   thr_list_create(     )
{
	pthread_t  pid;

	pid=thread_create();
	if(pid<0)
	{
		perror("pthread_create()");
		return -1;
	}
	thread_list_work();
}

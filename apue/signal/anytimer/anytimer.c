#include<stdio.h>
#include<stdlib.h>
#include"anytimer2.h"
struct mytimer
{
	int sec;
	at_jobfunc_t* jobp;
	void *arg;
	int status;
	int pos;
};
static struct mytimer* job[JOB_MAX];
int at_addjob(int sec, at_jobfunc_t *jobp,void *arg);
{
	struct mytimer *me;
	int pos;

	if(inited)
	{
		
	}
	me=malloc(sizeof(*me));
	if(me==NULL)
		return NULL;
	me->sec=sec;
	me->jobp=jobp;
	me->arg=arg;
	me->status=->
}
/*
 *	return	>= 0				成功，返回任务ID
 *			== -EINVAL			失败，参数非法
 *			== -ENOMEM			失败，内存分配失败
 *			== -ENOSPC			失败，任务数组已满	
 * */

int at_addjob_repeat(int sec, at_jobfunc_t *jobp,void *arg);
/*
 *	同上
 *
 * */


int at_canceljob(int id);
/*
 *	return	== 0 				成功，指定任务已取消
 *			== -EINVAL          失败，参数非法
 *			== -ECANCELED		失败，指定任务早已取消
 *			== -EBUSY			失败，指定任务已完成	
 *
 * */


int at_waitjob(int id);
/*
 *	return	== 0				成功，指定任务已释放
 *			== -EINVAL          失败，参数非法
 *			== -EBUSY           失败，指定任务为周期性任务	
 * */

/********************************************/

int at_stopjob(int id);

int at_resumejob(int id );



#endif




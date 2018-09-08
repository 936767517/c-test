#include"anytimer2.h"

#define JOB_RUN 001
#define JOB_OVE 002
#define JOB_CLE 004
#define JOB_STP 010
#define JOB_REP 020
struct mytimer
{
	int sec;
	at_jobfunc_t* jobp;
	void *arg;
	int status;
	int osec;
	int ostatus;
};

static struct mytimer* job[JOB_MAX];
int inited=1;
struct sigaction oact;
int get_free_pos(void)
{
	int i;
	for(i=0;i<JOB_MAX;i++)
		if(job[i]==NULL)
			return i;
	return -1;

}
void alarm_action(int s,siginfo_t *sic,void *m)
{
	int i;
	if(sic->si_code!=SI_KERNEL)
		return ;
	for(i=0;i<JOB_MAX;i++)
	{
		if(job[i]==NULL)
			continue;
		if(job[i]->status==JOB_RUN)
		{
			(job[i]->sec)-=1;
		}
		if(job[i]->sec==0)
		{
			if(job[i]->status==JOB_RUN)
			{
				job[i]->jobp(job[i]->arg);
				job[i]->status=JOB_OVE;
			}
			if(job[i]->status==JOB_REP)
			{
				job[i]->jobp(job[i]->arg);
				job[i]->sec=job[i]->osec;
			}
		}
	}
}
static void module_unload(void)
{
	int i;
	struct itimerval itv;

	itv.it_interval.tv_sec = 0;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 0;
	itv.it_value.tv_usec = 0;
	if(setitimer(ITIMER_REAL,&itv,NULL)<0)
		return ;


	if(sigaction(SIGALRM,&oact,NULL)<0)
		return ;

	for(i = 0 ; i < JOB_MAX ; i++)
		free(job[i]);	
}
static int  module_load(void)
{
	struct sigaction act;
	struct itimerval itv;
	act.sa_sigaction=alarm_action;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO;
	if(sigaction(SIGALRM,&act,&oact)<0)
	{
		return -1;
	}
	itv.it_interval.tv_sec=1;
	itv.it_interval.tv_usec=0;
	itv.it_value.tv_sec=1;
	itv.it_value.tv_usec=0;
	if(setitimer(ITIMER_REAL,&itv,NULL)<0)
	{
		return -1;
	}
	atexit(module_unload);
	return 0;
}	
int at_addjob(int sec, at_jobfunc_t *jobp,void *arg)
{
	struct mytimer *me;
	int pos;
	if(sec<=0)
		return -EINVAL;

	if(inited)
	{
		if(module_load()<0)
			return -1;
		inited=0;
	}
	me=malloc(sizeof(*me));
	if(me==NULL)
		return -ENOMEM;
	me->sec=sec;
	me->jobp=jobp;
	me->arg=arg;
	me->status=JOB_RUN;
	me->ostatus=JOB_RUN;
	pos=get_free_pos();
	if(pos<0)
		return -ENOSPC;
	me->osec=sec;
	job[pos]=me;
	return pos;
}
/*
 *	return	>= 0				成功，返回任务ID
 *			== -EINVAL			失败，参数非法
 *			== -ENOMEM			失败，内存分配失败
 *			== -ENOSPC			失败，任务数组已满
 *			== -1	
 * */

int at_addjob_repeat(int sec, at_jobfunc_t *jobp,void *arg)
{
	struct mytimer *me;
	int pos;
	if(sec<=0)
		return -EINVAL;

	if(inited)
	{
		module_load();
		inited=0;
	}
	me=malloc(sizeof(*me));
	if(me==NULL)
		return -ENOMEM;
	me->sec=sec;
	me->jobp=jobp;
	me->arg=arg;
	me->status=JOB_REP;
	me->ostatus=JOB_REP;
	pos=get_free_pos();
	if(pos<0)
		return -ENOSPC;
	me->osec=sec;
	job[pos]=me;
	return pos;
}
/*
 *	同上
 *
 * */


int at_canceljob(int id)
{
	if(id<0)
		return -EINVAL;
	if(job[id]==NULL)
		return -EINVAL;
	if(job[id]->status==JOB_CLE)
		return -ECANCELED;
	if(job[id]->status==JOB_OVE)	
		return -EBUSY;
	job[id]->status==JOB_CLE;
	return 0;
}
/*
 *	return	== 0 				成功，指定任务已取消
 *			== -EINVAL          失败，参数非法
 *			== -ECANCELED		失败，指定任务早已取消
 *			== -EBUSY			失败，指定任务已完成	
 *
 * */


int at_waitjob(int id)
{
	if(id<0)
		return -EINVAL;
	if(job[id]==NULL)
		return -EINVAL;
	if(job[id]->status==JOB_REP)
		return -EBUSY;
	while(1)
	{
		if(job[id]->status==JOB_OVE)
		{
			free(job[id]);
			job[id]=NULL;
			return 0;
		}
		pause();
	}
}
/*
 *	return	== 0				成功，指定任务已释放
 *			== -EINVAL          失败，参数非法
 *			== -EBUSY           失败，指定任务为周期性任务	
 * */

/********************************************/

int at_stopjob(int id)
{	
	if(id<0)
		return -EINVAL;
	if(job[id]==NULL)
		return -EINVAL;
	if(job[id]->status==JOB_OVE&&job[id]->status==JOB_CLE)
		return -EBUSY;
	if(job[id]->status==JOB_STP)
		return -ECANCELED;
	job[id]->status=JOB_STP;
	return 0;	
}

int at_resumejob(int id )
{	
	if(id<0)
		return -EINVAL;
	if(job[id]==NULL)
		return -EINVAL;
	if(job[id]->status!=JOB_STP)
		return -EINVAL;
	job[id]->status=job[id]->ostatus;
	return 0;
}






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
	pthread_mutex_t mut;
	pthread_cond_t cond;
};

static struct mytimer* job[JOB_MAX];
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static pthread_t tid;
int get_free_pos(void)
{
	int i;
	for(i=0;i<JOB_MAX;i++)
		if(job[i]==NULL)
			return i;
	return -1;

}
void *thr_alrm(void *p)
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mut_job);
		for(i=0;i<JOB_MAX;i++)
		{
			if(job[i]!=NULL)
			{
				pthread_mutex_lock(&job[i]->mut);
				if(job[i]->status==JOB_RUN)
				{
					(job[i]->sec)-=1;
					if(job[i]->sec==0)
					{
						job[i]->jobp(job[i]->arg);
						job[i]->status=JOB_OVE;
						pthread_cond_broadcast(&job[i]->cond);
					}
				}
				else if(job[i]->status==JOB_REP)
				{
					(job[i]->sec)-=1;
					if(job[i]->sec==0)
					{
						job[i]->jobp(job[i]->arg);
						job[i]->sec=job[i]->osec;
					}
				}
				else
				{
				}
				pthread_mutex_unlock(&job[i]->mut);
			}
		}
		pthread_mutex_unlock(&mut_job);
		sleep(1);
	}
	pthread_exit(NULL);
}
static void module_unload(void)
{
	int i;
	pthread_cancel(tid);
	pthread_join(tid,NULL);
	for(i = 0 ; i < JOB_MAX ; i++)
	{
		if(job[i]!=NULL)
		{
			pthread_mutex_destroy(&job[i]->mut);
			pthread_cond_destroy(&job[i]->cond);
			free(job[i]);	
		}
	
	}
	pthread_mutex_destroy(&mut_job);
}
static void  module_load(void)
{
	int err;
	err=pthread_create(&tid,NULL,thr_alrm,NULL);
	if(err)
	{
		fprintf(stderr,"pthread_create():%s\n",strerror(err));
		exit;
	}
	atexit(module_unload);

}	
int at_addjob(int sec, at_jobfunc_t *jobp,void *arg)
{
	struct mytimer *me;
	int pos;
	if(sec<=0)
		return -EINVAL;
	pthread_once(&init_once,module_load);
	
	me=malloc(sizeof(*me));
	if(me==NULL)
		return -ENOMEM;
	me->sec=sec;
	me->jobp=jobp;
	me->arg=arg;
	me->status=JOB_RUN;
	me->ostatus=JOB_RUN;
	me->osec=sec;
	pthread_cond_init(&me->cond,NULL);
	pthread_mutex_init(&me->mut,NULL);
	pthread_mutex_lock(&mut_job);
	pos=get_free_pos();
	if(pos<0)
	{
		pthread_mutex_unlock(&mut_job);
		return -ENOSPC;
	}
	job[pos]=me;
	pthread_mutex_unlock(&mut_job);
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

	pthread_once(&init_once,module_load);

	me=malloc(sizeof(*me));
	if(me==NULL)
		return -ENOMEM;
	me->sec=sec;
	me->jobp=jobp;
	me->arg=arg;
	me->status=JOB_REP;
	me->ostatus=JOB_REP;
	me->osec=sec;
	pthread_cond_init(&me->cond,NULL);
	pthread_mutex_init(&me->mut,NULL);
	pthread_mutex_lock(&mut_job);
	pos=get_free_pos();
	if(pos<0)
	{
		pthread_mutex_unlock(&mut_job);
		return -ENOSPC;
	}
	job[pos]=me;
	pthread_mutex_unlock(&mut_job);
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
	pthread_mutex_lock(&mut_job);
	if(job[id]==NULL)
	{
		pthread_mutex_unlock(&mut_job);
		return -EINVAL;
	}
	pthread_mutex_lock(&job[id]->mut);
	if(job[id]->status==JOB_CLE)
	{
		pthread_mutex_unlock(&job[id]->mut);
		return -ECANCELED;
	}
	else if(job[id]->status==JOB_OVE)
	{
		pthread_mutex_unlock(&job[id]->mut);
		return -EBUSY;
	}
	else
	{
		job[id]->status=JOB_CLE;
		pthread_cond_broadcast(&job[id]->cond);
	}
	pthread_mutex_unlock(&job[id]->mut);
	pthread_mutex_unlock(&mut_job);
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
	pthread_mutex_lock(&mut_job);
	if(job[id]==NULL)
	{
		pthread_mutex_unlock(&mut_job);
		return -EINVAL;
	}
	pthread_mutex_lock(&job[id]->mut);
	if(job[id]->status==JOB_REP)
	{
		pthread_mutex_unlock(&job[id]->mut);
		return -EBUSY;
	}
	while(job[id]->status!=JOB_OVE&&job[id]->status!=JOB_CLE)
	{
		pthread_cond_wait(&job[id]->cond,&job[id]->mut);
	}
	pthread_mutex_unlock(&job[id]->mut);
	pthread_mutex_destroy(&job[id]->mut);
	pthread_cond_destroy(&job[id]->cond);
	free(job[id]);
	job[id]=NULL;
	pthread_mutex_unlock(&mut_job);	

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
	pthread_mutex_lock(&mut_job);	
	if(job[id]==NULL)
	{
		pthread_mutex_unlock(&mut_job);	
		return -EINVAL;
	}
	pthread_mutex_lock(&job[id]->mut);
	if(job[id]->status==JOB_OVE&&job[id]->status==JOB_CLE)
	{
		pthread_mutex_unlock(&job[id]->mut);
		return -EBUSY;
	}
	if(job[id]->status==JOB_STP)
	{
		pthread_mutex_unlock(&job[id]->mut);
		return -ECANCELED;
	}
	job[id]->status=JOB_STP;
	pthread_mutex_unlock(&job[id]->mut);
	pthread_mutex_unlock(&mut_job);	
	return 0;	
}

int at_resumejob(int id )
{	
	if(id<0)
		return -EINVAL;
	pthread_mutex_lock(&mut_job);	
	if(job[id]==NULL)
	{
		pthread_mutex_unlock(&mut_job);	
		return -EINVAL;
	}
	pthread_mutex_lock(&job[id]->mut);	
	if(job[id]->status!=JOB_STP)
	{
		pthread_mutex_unlock(&job[id]->mut);	
		return -EINVAL;
	}
	job[id]->status=job[id]->ostatus;
	pthread_mutex_unlock(&job[id]->mut);
	pthread_mutex_unlock(&mut_job);	
	return 0;
}






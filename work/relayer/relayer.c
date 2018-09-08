#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFSIZE		1024

enum
{
	STATE_R=1,
	STATE_W,
	STATE_Ex,
	STATE_T
};


struct rel_fsm_st
{
	int state;
	int sfd;
	int dfd;
	char buf[BUFSIZE];
	int len;
	int pos;
	int64_t count;
	char *errstr;
};

struct rel_job_st
{
	int job_state;
	//int fd1,fd2;
	struct rel_fsm_st fsm12,fsm21;
//  struct timeval start,end;
	pthread_mutex_t mut_job_state;	
	pthread_cond_t cond_job_state;
};

static struct rel_job_st *rel_job[REL_JOBMAX];
static pthread_mutex_t mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once= PTHREAD_ONCE_INIT;
static void rel_fsm_init(struct rel_fsm_st* me)
{
	
	me->state=STATE_R;
	me->sfd=fd1;
	me->dfd=fd2;
	me->len=0;
	me->pos=0;
	me->count=0;
}
int get_free_pos(void)
{
	int i;
	for(i=0;i<REL_JOBMAX;i++)
	{
		if(rel_job[i]==NULL)
		{
			return i;
		}
	}
	return -1;
}
int rel_addjob(int fd1,int fd2)
{
	struct rel_job_st* me;
	int i;
	pthread_once(&init_once,module_load);
	if(fd1==NULL||fd2==NULL)
	{
		return -EINVAL;
	}
	me=malloc(sizeoe(*me));
	if(me==NULL)
	{
		perror("malloc()");
		return -ENOMEM;
	}
	me->job_state=STATE_RUNNING;
	pthread_mutex_init(&mut_job_state,NULL);
	pthread_cond_init(&cond_job_state,NULL);
	rel_fsm_init(&me->fsm12);
	rel_fsm_init(&me->fsm21);
	pthread_mutex_lock(&mut_rel_job);
	n=get_free_pos();
	if(n<0)
	{
		free(me);
		pthread_mutex_unlock(&mut_rel_job);
		return -ENOSPC;
	}
	job[n]=me;
	pthread_mutex_unlock(&mut_rel_job);
	return n;
}
/*
 *	return	>= 0			成功，返回任务ID
 *			== -EINVAL		失败，参数非法
 *			== -ENOMEM		失败，内存分配失败
 *			== -ENOSPC		失败，任务数组满	
 *
 * */

int rel_canceljob(int id)
{
	if(id<0)
		return -EINVAL;
	else 
	{
		if(job[id]==NULL)
			return -EINVAL;
		else if(job[id]->state==STATE_CANCELED||job[id]->state==STATE_OVER)
			return -EBUSY;
		else 
		{
			pthread_mutex_lock(&job[id]->mut_job_state);
			job[id]->state=STATE_CANCELED;
			pthread_mutex_unlock(&job[id]->mut_job_state);
			return 0;
		}
	}
}

/*
 *	return	== 0			成功，指定任务已取消
 *			== -EINVAL      失败，参数非法
 *			== -EBUSY		失败，指定任务早已被取消或完成	
 * */

int rel_waitjob(int id,struct rel_stat_st *rel_stat)
{
	if(id<0)
		return -EINVAL;
	if(job[id]==NULL)
		return -EINVAL;
	while(job[id]->state!=STATE_OVER&&job[id]->state!=STATE_CANCELED)
	{
		pthread_cond_wait(&job[id]->cond_job_state,&job[id]->mut_job_state);
	}
	
}
/*
 *	return  == 0            成功，指定任务已释放
 *			== -EINVAL      失败，参数非法
 * */


int rel_statjob(int id,struct rel_stat_st *);
/*
 *	return  == 0            成功，指定任务状态已返回
 *			== -EINVAL      失败，参数非法
 * */


static void fsm_driver(struct fsm_st *fsm)
{
	int ret;

	switch(fsm->state)
	{
		case STATE_R: 
			fsm->len = read(fsm->sfd,fsm->buf,BUFSIZE);
			if(fsm->len == 0)
				fsm->state = STATE_T;
			else if(fsm->len < 0)
				{
					if(errno == EAGAIN)
						fsm->state = STATE_R;
					else
					{
						fsm->errstr = "read()";
						fsm->state = STATE_Ex;
					}
				}
				else 
				{	
					fsm->pos = 0;
					fsm->state = STATE_W;
				}
			break;

		case STATE_W:
			ret = write(fsm->dfd,fsm->buf+fsm->pos,fsm->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_Ex;
				}	
			}
			else 
			{	
				fsm->pos += ret;	
				fsm->len -= ret;
				if(fsm->len == 0)
					fsm->state = STATE_R;
				else
					fsm->state = STATE_W;
			}

			break;

		case STATE_Ex:
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;

		case STATE_T:
			/*do sth*/
			break;

		default:
			abort();	

	}

}

static void relay(int fd1,int fd2)
{
	int fd1_save,fd2_save;
	struct fsm_st fsm12,fsm21;	

	fd1_save = fcntl(fd1,F_GETFL);
	fcntl(fd1,F_SETFL,fd1_save|O_NONBLOCK);
	
	fd2_save = fcntl(fd2,F_GETFL);
    fcntl(fd2,F_SETFL,fd2_save|O_NONBLOCK);


	fsm12.state = STATE_R;
	fsm12.sfd = fd1;
	fsm12.dfd = fd2;	

	fsm21.state = STATE_R;
	fsm21.sfd = fd2;
	fsm21.dfd = fd1;

	while(fsm12.state != STATE_T || fsm21.state != STATE_T)
	{	
		fsm_driver(&fsm12);
		fsm_driver(&fsm21);
	}

	fcntl(fd1,F_SETFL,fd1_save);
	fcntl(fd2,F_SETFL,fd2_save);

}



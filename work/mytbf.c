#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include "mytbf.h"

typedef void (*sighandler_t)(int);

struct mytbf_st
{
    int cps;
    int burst;
    int token;
	int pos;
};

static struct mytbf_st *job[MYTBF_MAX];
static int inited = 1;
//static sighandler_t alrm_handler_save;
struct sigaction oact;
struct itimerval oitimer;

static void sigaction(int s,siginfo_t *m,void *k)
{
	int i;

	//alarm(1);
	if(m->si_code== SI_KERNEL)
	{

		for(i = 0 ; i < MYTBF_MAX ; i++)
		{
			if(job[i] != NULL)
			{
				job[i]->token += job[i]->cps;
				if(job[i]->token > job[i]->burst)
					job[i]->token = job[i]->burst;
			}
		}
	}
}

static void module_unload(void)
{
	int i;

	//alarm(0);
	if(setitimer(ITIMER_REAL,&oitimer,NULL) < 0)
	{
		perror("setimtimer()");
		exit;
	}

	//signal(SIGALRM, alrm_handler_save);

	for(i = 0 ; i < MYTBF_MAX ; i++)
		free(job[i]);	

}

static void module_load(void)
{
	//alrm_handler_save = signal(SIGALRM,alrm_handler);
	//alarm(1);
	struct itimerval itimer;
	struct sigaction act;
	act.sa_sigaction=sigaction;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	itimer.it_interval.tv_sec = 1;
	itimer.it_interval.tv_usec =0;
	itimer.it_value.tv_sec= 1;
	itimer.it_value.tv.usec=0;
	if(setitimer(ITIMER_REAL,&itimer,&oitimer) < 0)
	{
		perror("setimtimer()");
		exit;
	}
	sigaction(SIGALRM,&act,&oact);
	atexit(module_unload);

}
static int get_free_pos(void)
{
	int i;

	for(i = 0 ; i < MYTBF_MAX ; i++)
		if(job[i] == NULL)
			return i;
	return -1;
}

mytbf_t *mytbf_init(int cps,int burst)
{
	struct mytbf_st *me;
	int pos;

	if(inited)
	{
		module_load();
		inited = 0;
	}


	me = malloc(sizeof(*me));
	if(me == NULL)
		return NULL;

	me->cps = cps;
	me->burst = burst;
	me->token = 0;

	pos = get_free_pos();
	if(pos < 0)
	{
		free(me);
		return NULL;
	}

	me->pos = pos;
	job[pos] = me;

	return me;

}

static int min(int a,int b)
{
	if(a < b)
		return a;
	return b;
}

int mytbf_fetchtoken(mytbf_t *ptr,int size)
{
	int n;
	struct mytbf_st *me = ptr;

	if(size < 0)
		return -EINVAL;

	while(me->token <= 0)
		pause();		

	n = min(me->token,size);
		
	me->token -= n;

	return n ;
}

int mytbf_returntoken(mytbf_t *ptr,int size)
{
	struct mytbf_st *me = ptr;

    if(size < 0)
        return -EINVAL;

	me->token += size;
	if(me->token > me->burst)
		me->token = me->burst;

	return 0;
}

void mytbf_destroy(mytbf_t *ptr)
{
	struct mytbf_st *me = ptr;	

	job[me->pos] = NULL;
	free(ptr);

	return ;
}



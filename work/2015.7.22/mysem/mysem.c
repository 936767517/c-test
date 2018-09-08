#include"mysem.h"

struct mysem_st
{
	int value;
	pthread_mutex_t mut;
	pthread_cond_t  cont;
};
static pthread_mutex_t mut_sem = PTHREAD_MUTEX_INITIALIZER；

mysem_t *mysem_init(int initval)
{
	mysem_st *ms;
	ms=malloc(sizeof(*ms));
	if(ms==NULL)
	{
		perror("malloc()");
		exit(NULL);
	}
	ms->value=initval;
	pthread_mutex_init(&ms->mut,NULL);
	pthread_cond_init(&ms->cont,NULL);

	return ms;
}
static min(int a,int b)
{
	if(a<b)
		return a;
	return b;
}
int mysem_sub(mysem_t *ptr,int size)
{
	int n;
	struct mysem_st *ms=ptr;
	if(size<0)
		return -EINVAL;
	pthread_mutex_lock(&ms->mut);
	while(ms->value<=0)
	{
		pthread_cond_wait(&ms->cont,&ms->mut);
	}
	n=min(size,ms->value);
	ms->value-=n;
	pthread_mutex_unlock(&ms->mut);
	return n;
	
}
int mysem_add(mysem_t *ptr,int size)
{
	struct mysem_st *ms=ptr;
	if(size<0)
		return -EINVAL;
	pthread_mutex_lock(&ms->mut);
	ms->value+=size;
	pthread_cond_broadcast(&ms->cont);
	pthread_mutex_unlock(&ms->mut);
	return 0;
}

int mysem_destroy(mysem_t *ptr)
{
	struct mysem_st *ms=ptr;
	pthread_mutex_destroy(&ms->mut);
	pthread_cond_d`estory(&ms->cont);
	free(ptr);
}




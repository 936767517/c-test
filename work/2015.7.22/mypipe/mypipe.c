#include"mypipe.h"

#define PIPESIZE 10
struct mypipe_st
{
	int head;
	int tail;
	int size;
	int max;
	char *data;
	pthread_mutex_t mut;
	pthread_cond_t cond;
};

mypipe_t* mypipe_init(int size)
{
	struct mypipe_st * me;
	me=malloc(sizeof(*me));
	if(me==NULL)
	{
		perror("malloc()");
		exit(NULL);
	}
	data=malloc(sizeof(*data)*size);
	if(data==NULL)
	{
		perror("malloc()");
		return NULL;
	}
	me->max=size;
	me->size=0;
	me->head=0;
	me->tail=me->head-1;
	pthread_mutex_init(&me->mut,NULL);
	pthread_cond_init(&me->cond,NULL);
	return me;
}
static int pipe_is_full(mypipe_t *ptr)
{
	struct mypipe_st *me=ptr;
	return me->size==me->max;
}
static int pipe_is_empty(mypipe_t *ptr)
{
	struct mypipe_st* me=ptr;
	return me->size==0;
}
static int min(int a,int b)
{
	if(a<b)
		return a;
	return b;
}
static int add_repeat(mypipe_st *me,int value,int n)
{
	//struct mypipe_st *me=ptr;
	int i;
	for(i=0;i<n;i++)
	{
		value++;
		if(value==me->max)
			value=0;
	}
	return value;
}
int mypipe_read(mypipe_t *ptr,char **buf,int size)
{
	struct mypipe_st* me=ptr;
	int n;
	int len=0;
	if(size<0)
	{
		return -1;
	}
	pthread_mutex_lock(&me->mut);
	while(1)
	{
		while(pipe_is_empty(ptr))
		{
			pthread_cond_wait(&me->cond,&me->mut);
		}
		n=min(me->size,size)
		memcpy(*buf+len,me->data+me->head,n);
		me->size-=n;
		me->head=add_repeat(me,me->head,n);
		len+=n;
		if(len==size)
		{
			break;
		}
	}
	pthread_cond_broadcast(&me->cond);
	pthread_mutex_unlock(&me->mut);
	return len;
}
int mypipe_write(mypipe_t *ptr,char *buf,int size)
{
	struct mypipe_st* me=ptr;
	int len=0;
	int num;
	if(size<0)
	{
		return -1;
	}
	pthread_mutex_lock(&me->mut);
	while(1)
	{
		while(pipe_is_full(ptr))
		{
			pthread_cond_wait(&me->cond,&me->mut);
		}
		num=min(size,me->max-me->size);
		memcpy(me->data+me->tail,buf+len,num);
		me->size+=num;
		me->tail=add_repeat(me,me->tail,num);
		len+=num;
		if(len==size)
		{
			break;
		}
	}

}
int mypipe_destroy(mypipe_t* ptr)
{
	struct mypipe_st *me=ptr;
	free(me->data);
	pthread_mutex_destroy(&me->mut);
	pthread_cond_destroy(&me->cond);
	free(ptr);
}



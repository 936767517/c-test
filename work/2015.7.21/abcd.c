#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N  4
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
   
int num=0;
void *print(void *m)
{
	while(1)
	{
	 pthread_mutex_trylock(&mut);
	 printf("%c",num);
	 pthread_mutex_unlock(&mut);
	 num=0;
	}
	pthread_exit(NULL);
}
int main()
{
	pthread_t tid[N];
	int n;
	int err;
	int i;
	for(n=0;n<N;n++)
	{
		err=pthread_create(tid+n,NULL,print,NULL);
		if(err)
		{
			exit(0);
		}
	}
	for(i='a';;i++)
	{
		while(num);
		if(i=='e')
		{
			i='a';
		}
		num=i;
		
	}
	for(n=0;n<N;n++)
	{
		pthread_join(tid[n],NULL);
	}

	return 0;
}

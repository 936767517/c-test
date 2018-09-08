#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LEFT		30000000
#define RIGHT		30000200
#define N 3
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
int num=0;
void *is_primer(void *m)
{
	int i,j,mark;
	while(1)
	{
		if(num==0)
		{
			continue;
		}
		if(num==-1)
		{
			break;
		}
		pthread_mutex_trylock(&mut);
		i=num;
		num=0;
		 pthread_mutex_unlock(&mut);
		mark=1;
		for(j=2;j<i/2;j++)
		{
			if(i%j==0)
			{
				mark=0;
				break;
			}
		}
		if(mark)
		{
			printf("%d is primer\n",i);
		}
	}
	pthread_exit(NULL);
}
int main()
{
	int i;
	int n;
	int err;
	pthread_t tid[N];
	for(n=0;n<N;n++)
	{
		err=pthread_create(tid+n,NULL,is_primer,NULL);
		if(err)
		{
			exit(0);
		}
	}

	for(i=LEFT;i<=RIGHT;i++)
	{
		while(num);

		//pthread_mutex_lock(&mut);
		num=i;
		//pthread_mutex_unlock(&mut);
	}

	num=-1;
	for(n=0;n<N;n++)
	{
		pthread_join(tid[n],NULL);
	}
	pthread_mutex_destroy(&mut);
	pthread_exit(NULL);
}



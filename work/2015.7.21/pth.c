#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *a(void *m)
{
	pthread_exit(NULL);
}
int main()
{
	int i;
	int err;
	pthread_t tid;
	for(i=0;i<100000;i++)
	{
		err=pthread_create(&tid,NULL,a,NULL);
		if(err)
		{
			exit(0);
		}
		pthread_join(tid,NULL);
	}


	return 0;
}

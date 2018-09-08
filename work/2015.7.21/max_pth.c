#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *a(void *m)
{
	while(1)
	pause();
}
int main()
{
	int i=0;
	int err;
	pthread_t tid;
	while(1)
	{
		err=pthread_create(&tid,NULL,a,NULL);
		if(err)
		{
			printf("error\n");
			exit(0);
		}
		i++;
			printf("i=%d\n",i);
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LEFT		30000000
#define RIGHT		30000200
void *is_primer(void *m)
{

	int i=*(int *)m;
	int j;
	int mark;
	mark=1;
	for(j = 2; j < i/2 ; j++)
	{
		if(i % j == 0)
		{
			mark = 0;
			break;
		}
	}
	if(mark)
		printf("%d is a primer.\n",i);		
	//pthread_exit(NULL);
}

int main()
{
	int i,mark;
	pthread_t p[1024];
	int res;

	for(i = LEFT; i <= RIGHT ; i++)
	{
		res=pthread_create((p+(i-LEFT)),NULL,is_primer,&i);
		if(res)
		{
			fprintf(stderr,"create():%s",strerror(res));
			exit(1);
		}
		}

	for(i = LEFT ;i <= RIGHT; i++)
	{
		pthread_join(p[i-LEFT],NULL);
	}
	

	exit(0);
}




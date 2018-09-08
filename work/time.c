#include<stdio.h>
#include<time.h>
int main()
{
	long long int i=0;
	time_t t=time(NULL);
	time_t r;
	while(1)
	{
		i++;
		r=time(NULL);
		if((r-t)==5)
		break;
	}
	printf("i=%lld\n",i);
	printf("r=%d\n",r);
	printf("t=%d\n",t);
	printf("r-t=%d\n",r-t);

	return 0;
}

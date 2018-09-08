#include<stdio.h>
#include<stdlib.h>
int main()
{
	long long int size=0;
	char *p=NULL;
	char *q=NULL;
	while(1)
	{
		p=malloc(1024*1024);
		if(p==NULL)
		{
			printf("size=%d\n",size);
			break;	
		}
		size=size+1;
		printf("size=%d",size);
	}
	//free(p);
	return 0;	
}

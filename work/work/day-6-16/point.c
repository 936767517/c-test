#include <stdio.h>
int main (void)
{
	char arr[5]={1,7,3,4,5};
	int  *p=((void*) 0);
	int i;
	printf("p=%p\n",p);
	printf("p=%p\n",p+3);
	for(i=0;i<5;i++)
	{
		printf("[%p][%p]\n",p+i,p);	
	}
	return 0;	
}

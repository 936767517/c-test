#include<stdio.h>
int main(void)
{
	int arr[5]={1,2,3,4,5};
	char a='5';
	int *p;
	int i;
	p=&a;
	printf("p=%p\n",p);
	printf("ap=%p\n",p+2);
	
	p=arr;
	printf("parr=%p\n",p);
	printf("p+2=%p\n",p+2);
	p=&arr[2];
	printf("parr[2]=%p\n",p);
	for(i=0;i<5;i++)
	{
		printf("%d ",*(p+i));	
	}
	return 0;	
}

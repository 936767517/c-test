#include<stdio.h>
#include<string.h>
int main(void)
{
	int a[100]={1,2,3,4,5};
	memcpy(a+1,a,16);
//	memmove(a+1,a,20);
	int i;
	for(i=0;i<5;i++)
	{
		printf("%d",a[i]);	
	}
	printf("\n");
	printf("sizeof=%d\n",sizeof(int));
	return 0;	
}

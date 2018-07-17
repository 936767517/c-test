#include<stdio.h>
int main(void)
{
	int arr[10];
	int num;
	int i=0;
	scanf("%d",&num);
	for(;num>0;)
	{
		arr[i]=num%10;
		i++;
		num=num/10;
	}
	while(--i>=0)
	{
		printf("arr[%d]=%d\n",i,arr[i]);	
	}
	return 0;	
}

#include<stdio.h>
int main(void)
{
	int a[10]={1,4,52,7,1,3,0,8,3,5};
	int i;
	int *max=&a[0];
	int *min=&a[0];
	for(i=0;i<sizeof(a)/sizeof(*a);i++)
	{
		if(*max<a[i])
		{
			max=&a[i];	
		}
		if(*min>a[i])
		{
			min=&a[i];	
		}
	}
	printf("max[%d]=%d\n",max-a,*max);
	printf("min[%d]=%d\n",min-a,*min);

	
	
	return 0;	
}

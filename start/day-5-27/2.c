#include <stdio.h>
int main(void)
{
	int num[30]={};
	float arr[6]={};
	int i;
	for(i=0;i<30;i++)
	{
		num[i]=2*(i+1);	
	}
	for(i=0;i<6;i++)
	{
		arr[i]=(num[0+5*i]+num[1+5*i]+num[2+5*i]+num[3+5*i]+num[4+5*i])/5;
		printf("arr[%d]=%f\n",i,arr[i]);
	}
	
	return 0;	
}

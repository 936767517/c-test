#include <stdio.h>
int fun(int a,int b,int c,int d,int e)
{
	int res=(a+b+c+d+e)/5;
	return res;
}
int main(void)
{
	int arr[30];
	float vau[6]={};
	int i,j;
	int num=2;
	for(i=0;i<30;)
	{
	
		if(num%2==0)
		{
			arr[i]=num;
			i++;
		}
		num++;		
	}
	for (j=0;j<6;j++)
	{
		vau[j]=fun(arr[j*5+0],arr[j*5+1],arr[j*5+2],arr[j*5+3],arr[j*5+4]);
		printf ("vau[%d]=%f\n",j,vau[j]);
	}
	
	
	return 0;	
}

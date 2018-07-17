#include <stdio.h>

double mypow(double a,int n)
{
	double res=1;
	int i;
	for(i=1;i<=n;i++)
	{
		res=res*a;	
	}
	return res;	
}
int main(void)
{
	int n=5;
	double a=5.0;
	double res=mypow(a,n);
	printf("res=%lf",res);
	
	return 0;	
}

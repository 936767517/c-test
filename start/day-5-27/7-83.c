#include<stdio.h>
int fun(int a,int b)
{
	int res=a-b;
	if(res<0)
	{
		res=res*(-1);	
	}
	return res;
}
int more(int a ,int b ,int c )
{
	int max;
	max=((a>b&&a>c)?a:(b>c?b:c));
	return max;
}
int main(void)
{
	int a=1;
	int b=-5;
	int c=fun(a,b);
	int max=more(1,2,3);
	printf("max=%d",max);
	printf("c=%d\n",c);

	return 0;
}

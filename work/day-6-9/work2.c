#include<stdio.h>
int btw(int a,int b,int c)
{
	
	return  (a>=b?(a>=c?a:c):(b>=c?b:c));
	
}
int main(void)
{	
	int a,b,c;
	scanf("%d %d %d",&a,&b,&c);
	int res=btw(a,b,c);
	printf("max=%d\n",res);

	return 0;
}

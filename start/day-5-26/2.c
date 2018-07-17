#include <stdio.h>
int main(void)
{
	int sum=0;
	int each=2;
	int day=0;
	float res;
	while((sum+each)<=100)
	{
		sum=sum+each;
		each=2*each;
		day=day+1;
	}
	res=0.8*(float)sum/day;
	printf(" res=%f\n sum=%d\n day=%d\n",res,sum,day);
	return 0;	
}

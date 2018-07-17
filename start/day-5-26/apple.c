#include <stdio.h>
int main(void)
{
	int day=0;
	int num=0;
	int ev=2;
	float mon;
	while((num+ev)<=100)
	{
		num=num+ev;
		ev=ev*2;
		day=day+1;
	}
	/*num=num-(ev/2);
	day=day-1;*/
	mon=0.8*num/day;
	printf("mon=%f\n num=%d\n day=%d\n ev=%d\n",mon,num,day,ev);
	return 0;
}

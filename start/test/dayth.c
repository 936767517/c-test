#include<stdio.h>
int main(void)
{
	int year,month,dayth;
	int day;
	scanf("%d-%d-%d",&year,&month,&dayth);
	printf("year=%d month=%d dayth=%d\n",year,month,dayth);
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			day=31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			day=30;
			break;
		case 2:
			day=28;
			break;
		default:
			day=0;
			break;
	}
	if(month==2&&((year%400==0)||(year%4==0&&year%100!=0)))
	{
		day=day+1;
	}
	printf("day=%d\n",day);
	return 0;
}

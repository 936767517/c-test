#include <stdio.h>

int main(void)
{
	int year, month, day;
	int days = 0;

	scanf("%d-%d-%d", &year, &month, &day);
	
	switch(month)
	{
		case 12: days += 30;
		case 11: days += 31;
		case 10: days += 30;
		case 9 : days += 31;
		case 8 : days += 31;
		case 7 : days += 30;
		case 6 : days += 31;
		case 5 : days += 30;
		case 4 : days += 31;
		case 3 : days += 28;
		case 2 : days += 31;
		case 1 : days += day;
	}
	
	if((month > 2) &&
		((year%400==0) || (year%4==0&&year%100!=0)))
	{
		days += 1;
	}

	printf("days = %d\n", days);

	return 0;
}

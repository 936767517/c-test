#include <stdio.h>

int main(void)
{
	int year, month;
	int days = 0;

	scanf("%d-%d", &year, &month);

	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;
		case 2:
			days = 28;
			break;
		default :
			days = 0;
	}

	if((month == 2) &&
		((year%400==0) || (year%4==0&&year%100!=0)))
	{
		days += 1;
	}

	printf("days = %d\n", days);
	
	return 0;
}

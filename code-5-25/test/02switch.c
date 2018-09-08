#include <stdio.h>

int main(void)
{
	int day = 0;

	scanf("%d", &day);

	switch(day)// switch(整型变量)
	{
		// case 整型常量 :
		case 1: 
		case 2:
		case 3:
			printf("three\n");
			break;
		case 4:
		case 5:
		case 6:
			printf("six\n");
			break;
		case 7:
		case 8:
		case 9:
			printf("seven\n");
			break;
		case 10 ... 12:
			printf("abc\n");
			break;
		default :
			printf("input data error\n");
	}
	
	return 0;
}

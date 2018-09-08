#include <stdio.h>

int main(void)
{
	int day = 0;

	scanf("%d", &day);

	switch(day)// switch(整型变量)
	{
		// case 整型常量 :
		case 1: 
			printf("one\n");
			break;
		case 2:
			printf("two\n");
			break;
		case 3:
			printf("three\n");
			break;
		case 4:
			printf("four\n");
			break;
		case 5:
			printf("five\n");
			break;
		case 6:
			printf("six\n");
			break;
		case 7:
			printf("seven\n");
			break;
		default :
			printf("input data error\n");
	}
	
	return 0;
}

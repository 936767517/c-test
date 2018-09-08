#include <stdio.h>

int atoi(char *str)
{
	int sum = 0;
	int flag = 1;

	if('-' == *str)
	{
		str++;
		flag = -1;
	}

	while(*str != '\0')
	{
		sum = sum * 10 + (*str - '0');
		str++;
	}
	return (sum * flag);
}

/*
 *itoa: @num change to string stored in @str
 * @num : + -
 * @str: string must be empty string
 * */
void itoa(int num ,char *str)
{
	if(num < 0)
	{
		*str = '-';
		*(str + 1) = '\0';
		num *= -1;
	}

	if(num / 10 != 0)
	{
		itoa(num / 10, str);
	}

	for(;*str != '\0'; str++);

	*str = num % 10 + '0';
	*(str + 1) = '\0';
}

float atof(char *str)
{
	int sum = 0;
	int base = 0;
	int flag = 1;

	if('-' == *str )
	{
		str++;
		flag = -1;
	}

	while(*str != '\0')
	{
		if(*str != '.')
		{
			sum = sum * 10 + (*str - '0');
			base *= 10;
		}
		else
		{
			base = 1;
		}
		
		str++;
	}

	if(0 == base)
		base = 1;
	return (float)sum / base * flag;
}

int main(void)
{
	int num;
	float res;
	char str[100] ={};
#if 0
	scanf("%s", str);

	num = atoi(str);
	printf("num = %d\n", num);
#endif

#if 0
	scanf("%d", &num);
	*str = '\0';
	itoa(num, str);
	printf("str = %s\n", str);
#endif

	scanf("%s", str);

	res = atof(str);
	printf("res = %f\n", res);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

// $ ./a.out 12 + 234
// 12+234=??

int add_(int a, int b)
{
	return a+b;
}
int sub_(int a, int b)
{
	return a-b;
}
int mul_(int a, int b)
{
	return a*b;
}
int div_(int a, int b)
{
	return a/b;
}

int main(int argc, char **argv)
{
	if(argc < 4)
	{
		printf("Usage...\n");
		return -1;
	}

	int (*funp[4])(int, int) = {add_, sub_, mul_, div_};

	int res;
	int value1, value2;

	value1 = atoi(argv[1]);
	value2 = atoi(argv[3]);

	switch(*argv[2])
	{
		case '+':
			res = add_(value1, value2);
			break;
		case '-':
			res = sub_(value1, value2);
			break;
		case 'x':
			res = mul_(value1, value2);
			break;
		case 'd':
			res = div_(value1, value2);
			break;
	}

	printf("%s %s %s = %d\n",
		argv[1], argv[2], argv[3], res);

	return 0;
}


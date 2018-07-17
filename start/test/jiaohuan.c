#include <stdio.h>
int main(void)
{
	int a=1,b=2;
#if 1
	a=a+b;
	b=a-b;
	a=a-b;
#endif
	printf("a=%d b=%d",a,b);

	return 0;
}

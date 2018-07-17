#include <stdio.h>
int main(void)
{
	int a=5;
	int b=a^4;
	printf("b=%d\n",b);
	int c=a<<1;
	printf("c=%d\n",c);
	int d=a&(~(1<<(3-1)));
	printf("d=%d\n",d);
	return 0;	
}

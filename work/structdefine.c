#include<stdio.h>
int main(void)
{
	struct item{
		int a;
		int b;
	};
	struct item a={
	.a =10,
	.b =13
	};
	printf("%d\n",a.b);
}

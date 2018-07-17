#include <stdio.h>
int main(void)
{
	
	int x;
	int y;
	char a;
	char b;
	char c;
	char d;
//	scanf("%c",&a);
//	scanf("%c",&b);
	scanf("%d %d",&x,&y);
//	scanf("%d",&x);
//	scanf("%d",&y);
	printf("********\n");
	scanf("%c %c",&a,&b);
	printf("ab%d-%d-%c-%c-\n",x,y,a,b);
	scanf("%c %c",&c,&d);
//	printf("ab%d-%d-%c-%c-\n",x,y,a,b);
	printf("c=%c,d=%c",c,d);

//	printf("a = %c\n", a);
//	printf("b = %c\n", b);
//	printf("x = %d\n", x);
//	printf("y = %d\n", y);
	return 0;
}

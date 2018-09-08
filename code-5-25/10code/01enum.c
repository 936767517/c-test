#include <stdio.h>

#define WHILE 0
enum node {white=0x255, black=0, yellow=0x123, red=0x234, blue=0xabc,
		green=0xbcd, grey=0x345, pink};

int main(void)
{
	enum node n1 = white;
	int i = black;
	
	printf("size = %d\n", sizeof(enum node));
	printf("size = %d\n", sizeof(n1));

	printf("red = %d\n", red);

	return 0;
}

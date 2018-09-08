#include <stdio.h>

struct node {
	/* type name:N;
	*  type : int short long char (signed, unsigned)
	*  N <= sizeof(name)
	* */
	int a:3;
	char c:3;
	signed i:8;
	unsigned char uc:2;
	short s:5;
	//float f:8; // error
};

int main(void)
{
	// sizeof(struct node) % 4 == 0
	printf("size = %d\n", sizeof(struct node));
	
	return 0;
}

#include <stdio.h>

struct node {
	char c1[9];
	double d;
};

int main(void)
{
	int i;
	struct node n1;
	printf("size = %d\n", sizeof(struct node));
	
	return 0;
}

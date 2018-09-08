#include <stdio.h>

struct node {
	int i1;
	char c1;
	char name[34];
	int i2;
	char c2;
};

int main(void)
{
	struct node n1 = {48, 'a', 50, 'A'};

	//printf("size = %d\n", sizeof(n1));
	
	printf("n1    = %p\n", &n1);
	printf("n1.i1 = %p\n", &n1.i1);
	printf("n1.c1 = %p\n", &n1.c1);
	printf("n1.i2 = %p\n", &n1.i2);
	printf("n1.c2 = %p\n", &n1.c2);

	int *p = &n1.i2;
	size_t n = (size_t)(&((struct node *)0)->i2);
	printf("n = %lu\n", n);
	printf("n1    = %p\n", ((char *)p - n));
	printf("n1    = %c\n", ((struct node *)((char *)p - n))->c1);

	return 0;
}

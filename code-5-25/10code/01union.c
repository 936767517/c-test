#include <stdio.h>

union node {
	char c;
	int i;
	short s;
};

struct info {
	int id;
	char name[25];
	union {
		int s_score;
		float t_score;
	}score;
};

int main(void)
{
	printf("size = %d\n", sizeof(union node));

	union node n1;

	n1.i = 256;
	printf("n1.c = %c %d\n", n1.c, (int)n1.c);
	printf("n1.i = %d\n", n1.i);

	//n1.i = 48;
	//printf("n1.i = %d\n", n1.i);
	
	return 0;
}

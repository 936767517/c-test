#include <stdio.h>

struct node {
	int i;
	struct node *next;
};

int main(void)
{
	struct node n1 = {1, NULL};
	struct node n2 = {2, &n1};
	struct node n3 = {3, &n2};
	struct node n4 = {4, &n3};
	struct node n5 = {5, &n4};
	struct node n6 = {6, &n5};
	struct node *p = &n6;
	struct node *q;

	printf("n4.i = %d\n", p->i);
	printf("n3.i = %d\n", p->next->i);
	printf("n2.i = %d\n", p->next->next->i);

	for(q = p; q != NULL; q = q->next)
	{
		printf("%d ", q->i);
	}
	printf("\n");

	return 0;
}

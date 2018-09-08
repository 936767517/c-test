#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 变长结构

struct node {
	int size;
	char data[0];
};

int main(void)
{
	int arr[4] = {1,2,3,43};
	printf("size = %d\n", (int)sizeof(struct node));

	struct node *p = (struct node *)malloc(sizeof(*p)+sizeof(int)*4);
	/* if error */

	memcpy(p->data, arr, sizeof(arr));

	printf("%d\n", *(int *)p->data);
	printf("%d\n", *(int *)(p->data+4));
	
	return 0;
}



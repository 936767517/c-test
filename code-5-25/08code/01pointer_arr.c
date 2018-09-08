#include <stdio.h>

int main(void)
{
	int i;
	int arr[5] = {1,2,3,4,5};
	// arr &arr[0]
	int *p = &arr[0];
	int *q = arr;
	int *m; // 野指针，其是造成段错误的根源所在

	printf("*q = %d\n", *q);

	for(i = 0; i < 5; i++, p++) // 当循环完成后指针p成为野指针
	{
		//printf("%d ", i[arr]);
		//printf("%d ", arr[i]);
		//printf("%d ", p[i]);
		//printf("%d ", *p);
		//printf("%p %p\n", (q + i), &arr[i]);
		//printf("%d ", *(q + i)); // q[i]
		//printf("%d ", *(i + q)); // i[q]
	}
	printf("\n");

	return 0;
}

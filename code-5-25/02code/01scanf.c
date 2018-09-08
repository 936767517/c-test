#include <stdio.h>

int main(void)
{
	int data;
	int n;

	// ' '或'\n'表示匹配任意多个' '或'\n'
	scanf("%d %d", &data, &n);

	printf("%d,%d\n", data, n);
	
	return 0;
}

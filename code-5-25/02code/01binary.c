#include <stdio.h>

int main(void)
{
	int bit;
	int data;

	scanf("%d", &data);

	for(bit = 32; bit > 0; bit--)
	{
		printf("%d", (data >> (bit - 1)) & 0x1 );
	}
	printf("\n");
	
	return 0;
}

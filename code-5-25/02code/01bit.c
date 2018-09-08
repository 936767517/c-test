#include <stdio.h>

int main(void)
{
	int data;
	int bit;
	int res;

	scanf("%d %d", &data, &bit);

	//data = data | (0x1 << (bit - 1)); // 设置
	//data = data & (~(0x1 << (bit - 1))); // 取消
	//data = data ^ (0x1 << (bit - 1)); // 置反
	res = (data >> (bit - 1)) & 0x1; // 读取

	printf("res = %d\n", res);
	printf("data = %d\n", data);
	
	return 0;
}

#include <stdio.h>

int msg_a = 5;

void msg()
{
	printf("extern.c:msg()msg_a = %d\n", msg_a);

	msg_a++;
}

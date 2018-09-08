#include <stdio.h>

#include "fb_draw.h"
int main(void)
{
	char ch;

	init_keyboard();
	while (1) {
		ch = getchar();
		if (ch == 'a') {
			printf("press a\n");
		}else 
			printf("none\n");
	}

	recover_keyboard();
	return 0;
}

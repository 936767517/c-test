#include <stdio.h>

int main(void)
{
	int i = 0;

	loop:
		printf("%d ", i++);
		if(i < 10)
		{
			goto loop;
		}
		if(i >= 10)
		{
			goto end;
		}

	end:
		printf("end\n");
	
	return 0;
}

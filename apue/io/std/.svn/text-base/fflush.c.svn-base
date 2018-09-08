#include <stdio.h>
#include <stdlib.h>

/*
 *	缓冲区：在绝大多数情况下，缓冲区的存在是件好事，作用是合并系统调用	
 *
 *	行缓冲：换行的时候刷新，满了的时候刷新，强制刷新（标准输出是这种模式，因为涉及到了终端设备）
 *
 *	全缓冲：满了的时候刷新，强制刷新（默认，只要不是终端设备）
 *
 *	无缓冲：stderr，需要立即输出
 * */


int main()
{
	int i;

	for(i = 0 ; i < 5 ; i++)
	{
		putchar('x');
		fflush(stdout);
		sleep(1);
	}

	exit(0);
}



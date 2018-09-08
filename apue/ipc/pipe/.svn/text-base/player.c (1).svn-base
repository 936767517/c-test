#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE		1024

int main()
{
	int pd[2];
	pid_t pid;
	int len;
	char buf[BUFSIZE];

	if(pipe(pd) < 0)
	{
		perror("pipe()");
		exit(1);
	}

	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid == 0)		// child
	{
		close(pd[1]);		// 关闭写端
		dup2(pd[0],0);	
		execXX("/usr/local/bin/mpg123","mpg123","-");
		perror("execXX()");
		....
		exit(0);
	}
	else				// parent
	{
		close(pd[0]);	// 关闭读端	
		//从网络上接收数据，写管道。
		close(pd[1]);
		wait(NULL);
		exit(0);
	}
}



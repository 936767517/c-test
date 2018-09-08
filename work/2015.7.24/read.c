#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
int main()
{
	int fd;
	int len;
	char buf[1024];
	fd=open("tmp",O_RDONLY);
	if(fd<0)
	{
		perror("open()");
		exit(0);
	}
	len=read(fd,&buf,1024);
	if(len<0)
	{
		perror("read()");
		exit(0);
	}
	printf("len=%d\n",len);

	return 0;
}

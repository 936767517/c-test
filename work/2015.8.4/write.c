#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	fd=open("tmp",O_RDWR|O_CREAT|O_TRUNC,0666);
	if(fd<0)
	{
		perror("open()");
		return -1;
	}
	FILE *fp;
	fp=fdopen(fd,"w+");
	int res;
	res=fprintf(fp,"nuima");
	printf("res=%d\n",res);
	return 0;
}

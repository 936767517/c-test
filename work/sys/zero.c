#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd;
	long long int count=1024;
	long long int bs=1024*1024*5;
	long long int res;
	fd=open("zero",O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(fd<0)
	{
		perror("open()");
		return -1;	
	}
	res=lseek(fd,count*bs,SEEK_END);
	write(fd,"a",1);
	printf("res=%lld\n",res);
	return 0;
}

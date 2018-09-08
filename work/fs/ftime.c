#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
int main()
{
	int fd;
	fd=open("test",O_WRONLY|O_APPEND|O_CREAT|O_TRUNC,0666);
	if(fd==-1)
	{
		perror("fopen()");	
		return -1;
	}

	time_t stamp;
	char buf[1024];
	struct tm* tm;
	ssize_t res;
	while(1)
	{
		time(&stamp);
	tm=localtime(&stamp);
	strftime(buf,1024,"%Y-%m-%d %H:%M:%S\n",tm);
	res=write(fd,buf,strlen(buf));
	sleep(1);
	}
	close (fd);
	return 0;	
}

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
#include<errno.h>
#define BUFSIZE 16384
int main(int argc,char **argv)
{
	if(argc<3)
	{
		fprintf(stderr,"Usage...\n");	
		return -1;
	}
	int src;
	int dest;
	char buff[BUFSIZE];
	int res;
	int pos;
	int ret;
	while(1)
	{
	src=open(argv[1],O_RDONLY);
	if(src<0)
	{
		if(errno==EINTR)
		{
			continue;
		}
		perror("open()");
		return -1;
	}
	else
	{
		break;
	}
	}
	
	dest=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(dest<0)
	{
		close(src);
		perror("open()");
		return -1;
	}
	
	while(1)
	{
		res=read(src,buff,BUFSIZE);
		if(res<1)
		{
			perror("read()");
			break;	
		}
		pos=0;
		while(res>0)
		{
			ret=write(dest,buff+pos,res);
			if(ret<0)
			{
				perror("write()");
				return -1;
			}
			res-=ret;
			pos+=ret;
		}
	}
	close(dest);
	close(src);
	return 0;	
}

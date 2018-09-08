#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include<signal.h>
#define BUFSIZE	1000
	int sfd,dfd = 1;
	char buf[BUFSIZE];
	int flag=1;
static void slow(int s)
{

	int len,ret,pos;
	do
	{
		len = read(sfd,buf,BUFSIZE);
		if(len == 0)
		{
			flag=0;
			break;
		}
			if(errno == EINTR)
			{
				perror("read()");
				continue;
			}
			break;
	}while(len<0);
		// len > 0

		pos = 0;

		while(len > 0)
		{
			ret = write(dfd,buf+pos,len);
			if(ret < 0)
			{
				if(errno == EINTR)
					continue;
				perror("write()");
				break;
			}
			len -= ret;
			pos += ret;
		}

	alarm(1);

}
int main(int argc,char **argv)
{

	if(argc < 2)
	{
		fprintf(stderr,"Usage:%s <srcfile>\n",argv[0]);
		exit(1);
	}

	do
	{
		sfd = open(argv[1],O_RDONLY);
		if(sfd < 0)
		{
			if(errno != EINTR)
			{
				perror("open()");
				exit(1);
			}
		}
	}while(sfd < 0);
	
	signal(SIGALRM,slow);
	alarm(1);
		while(1)
		{
			if(flag==0)
			{
				break;
			}
		}
				close(sfd);

	exit(0);
}

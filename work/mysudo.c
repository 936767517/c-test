#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char **argv)
{
	pid_t pid;
	struct passwd name;
	pid=fork();
	if(pid<0)
	{
		return -1;
	}
	if(pid==0)
	{
		&name=getpwnam(argv[1]);
		setuid(name.pw_uid);
		execl(/bin/cat,argv[2],argv[3]);
		return 0;
	}
	wait(NULL);

	return 0;
}

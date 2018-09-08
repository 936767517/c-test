#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<glob.h>

int main(int argc,char **argv)
{
	char path[1024]="/bin/";
	glob_t globres;
	int pid;
	if(argc<2)
	{
		printf("Usage...\n");
		return -1;
	}
	strncat(path,argv[1],1024);
	if(glob(path,0,NULL,&globres)!=0)
	{
		printf("command not found\n");
		return -1;
	}
	pid=fork();
	if(pid<0)
	{
		perror("fork()");
		return -1;
	}
	if(pid==0)
	{
		execv(path,&argv[1]);
		perror("execl()");
		return 0;
	}
	wait(NULL);

	return 0;
}

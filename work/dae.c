#include<stdio.h>
#include<unistd.h>
int daemomize()
{
	int res;
	int pid;
	res=fork();
	if(res<0)
	{
		perror("fork()");
		return -1;
	}
	if(res>0)
	{
		return -1;
	}
	else if(res==0)
	{
		pid=setsid();
		if(pid<0)
		{
			perror("setsid()");
			return -1;
		}
	}

}
int main()
{
	FILE *fp;
	fp=fopen("tmp","w");
	if(fp==NULL)
	{
		perror("fopen()");
		return -1;
	}
	daemomize();
	while(1)
	{
		sleep(5);
		fputc('a',fp);
	}
	fclose(fp);
	return 0;
}

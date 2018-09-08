#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#define  MEM_TYPE 'M'
#define MEM_RESET   _IO(MEM_TYPE,1)
#define MEM_RESIZE  _IOW(MEM_TYPE,2,int)

int main(int argc,char **argv)
{
	int fd,ret,value;
	if((argc !=3)&&(argc!=4))
	{
		printf("Usage:....\n");
		exit(1);
	}
	fd=open(argv[1],O_RDWR);
	if(fd==-1)
	{
		printf("cannot open %s\n",argv[1]);
		exit(1);
	}
	if(strncmp(argv[2],"reset",5)==0){
		ret=ioctl(fd,MEM_RESET);
	}
	else if(strncmp(argv[2],"resize",6)==0){
		value =atoi(argv[3]);
		ret=ioctl(fd,MEM_RESIZE,value);
	}
	else{
		printf("only reset resize\n");
		exit(1);
	}
	if(ret)
		printf("%s %s failed\n ",argv[2],argv[1]);
	else
		printf("%s %s sucess\n ",argv[2],argv[1]);
	close(fd);
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
int fblock(char *path)
{
	struct stat statres;
	if(lstat(path,&statres)<0)
	{
		perror("stat()");
		return 0;
	}
	return statres.st_blocks;
		
}
int fmode(char *path)
{
	struct stat statres;
	if(lstat(path,&statres)<0)
	{
		perror("stat()");
		return -1;
	}
	if(S_ISDIR(statres.st_mode))
	{
		return 1;	
	}
	else 
	{
		return 0;	
	}
}
int   myglob(char *pattern,glob_t *globres);
int mydu(char *path)
{
	int sum=0;
	int i;
	char q[1024];
	char *p;
	glob_t globres;
	if(fmode(path)==0)
	{
		return fblock(path);	
	}
	else if(fmode(path)==1)
	{
		strncpy(q,path,1024);
		strncat(q,"/*",1024);
		//snprintf(q,2,"/*");
		if(myglob(path,&globres)==-1)
		{
			return -1;	
		}
		for(i=0;i<globres.gl_pathc;i++)
		{
			sum+=mydu(globres.gl_pathv[i]);
		}
		strncpy(q,path,1024);
		strncat(q,"/.*",1024);
		//snprintf(q,3,"/.*");
		if(myglob(q,&globres)==-1)
		{
			return -1;	
		}
		for(i=0;i<globres.gl_pathc;i++)
		{
			p=strrchr(globres.gl_pathv[i],'/');
			if(strcmp(p+1,".")!=0&&strcmp(p+1,"..")!=0)
			{
				sum+=mydu(globres.gl_pathv[i]);	
			}
			else
			{
				break;	
				
			}
		}
		return sum;
	}
	return 0;
}
int   myglob(char *pattern,glob_t *globres)
{
	int err;
	err=glob(pattern,0,NULL,globres);
	if(err)
	{
		fprintf(stderr,"glob()err=%d\n",err);
		return -1;
	}
	return 0;
}
int main(int argc,char **argv)

{
	int res=0;
	if(argc<2)
	{
		fprintf(stderr,"Usage...\n");
		return -1;
	}
	res=mydu(argv[1])/2;
	printf("%d\t%s\n",res,argv[1]);
	return 0;	
}

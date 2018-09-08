#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include <time.h>
#include <glob.h>
#include <pwd.h>
#include <grp.h>

#define TIMESTRSIZE 1024
#define PATHSIZE 1024

static int  fmode(const char *type,const char *fname,const struct stat fp)
//static int  fmode(const char *type,const char *fname)
{
	//struct stat fp;
	char perm[1024]={};
	int res;
	struct passwd *pwdline;
	struct group *gidline;
	/*if(stat(fname,&fp)<0)
	{
		perror("stat()");
		return 1;
	}*/
	mode_t mode=(fp.st_mode&S_IFMT);//判断文件类型
	switch(mode)
	{
		case S_IFSOCK:
		*(perm+0)='s';
		res='s';
		break;
		case S_IFLNK:
		*(perm+0)='l';
		res='l';
		break;
		case S_IFREG:
		*(perm+0)='-';
		res='-';
		break;
		case S_IFBLK:
		*(perm+0)='b';
		res='b';
		break;
		case S_IFDIR:
		*(perm+0)='d';
		res='d';
		break;
		case S_IFCHR:
		res='c';
		*(perm+0)='c';
		break;
		case S_IFIFO:
		*(perm+0)='p';
		res='p';
		break;
		default:
		res= -1;
		break;
	}
	mode=(fp.st_mode&S_IRWXU);//判断权限
	if((mode&S_IRUSR) ==S_IRUSR )//user的读
	{
		*(perm+1)='r';	
	}
	else
	{
		*(perm+1)='-';	
	}
	if((mode&S_IWUSR) ==S_IWUSR )//写
	{
		*(perm+2)='w';	
	}
	else
	{
		*(perm+2)='-';	
	}
	if((mode&S_IXUSR) ==S_IXUSR )//执行
	{
		if((fp.st_mode&S_ISUID)==S_ISUID)
		{
			*(perm+3)='s';
		}
		else 
		{
			*(perm+3)='x';	
		}
	}
	else
	{
		*(perm+3)='-';	
	}
	mode=(fp.st_mode&S_IRWXG);//判断权限
	if((mode&S_IRGRP )==S_IRGRP )//group的读
	{
		*(perm+4)='r';	
	}
	else
	{
		*(perm+4)='-';	
	}
	if((mode&S_IWGRP )==S_IWGRP)//写
	{
		*(perm+5)='w';	
	}
	else
	{
		*(perm+5)='-';	
	}
	if((mode&S_IXGRP )==S_IXGRP )//执行
	{
		if((fp.st_mode&S_ISGID)==S_ISGID)
		{
			*(perm+6)='s';
		}
		else 
		{
			*(perm+6)='x';	
		}
	}
	else
	{
		*(perm+6)='-';	
	}
	mode=(fp.st_mode&S_IRWXO);//判断权限
	if((mode&S_IROTH )==S_IROTH )//other的读
	{
		*(perm+7)='r';	
	}
	else
	{
		*(perm+7)='-';
	}
	if((mode&S_IWOTH) ==S_IWOTH )//写
	{
		*(perm+8)='w';	
	}
	else
	{
		*(perm+8)='-';	
	}
	if((mode&S_IXOTH )==S_IXOTH )//执行
	{
		if((fp.st_mode&S_ISVTX)==S_ISVTX)
		{
			*(perm+9)='t';
		}
		else 
		{
			*(perm+9)='x';	
		}
	}
	else
	{
		*(perm+9)='-';	
	}
	*(perm+10)='.';
	*(perm+11)='\0';
	printf("%s",perm);
	if(strcmp(type,"-n")==0)
	{
		printf("%2d%2d%2d",fp.st_nlink,fp.st_uid,fp.st_gid);
	}
	if(strcmp(type,"-l")==0)
	{
		pwdline=getpwuid(fp.st_uid);
		gidline=getgrgid(fp.st_gid);
		printf("%2d %s %s",fp.st_nlink,pwdline->pw_name,gidline->gr_name);
	}
		printf(" %d",fp.st_size);
	struct tm *tm;
	char timestr[TIMESTRSIZE];
	tm=localtime(&fp.st_mtime);
	strftime(timestr,TIMESTRSIZE,"%b %d %H:%m",tm);
	printf(" %s",timestr);
	if(res=='d')
	{
		printf(" \033[36m%s",fname);
		printf("\033[0m");
	}
	else
	{
		printf(" %s",fname);	
	}
	printf("\n");
	return res;
}
int f_stat(char *fname,struct stat *fp)
{
	if(stat(fname,fp)<0)
	{
		perror("stat()");
		return -1;
	}
	return 0;
}
void fglob(char *pattern,glob_t* globres)
{
	char path[PATHSIZE];
	strncpy(path,pattern,PATHSIZE);
	strncat(path,"/*",PATHSIZE);
	glob(path,0,NULL,globres);
}
int main(int argc,char **argv)
{
	//char perm[11]={};
	struct stat fp;
	glob_t globres;
	int i;
	if(argc<2)
	{
		fprintf(stderr,"Usage....\n");
		return 1;
	}
	if(f_stat(argv[2],&fp)==-1)
	{
		return -1;	
	}
	mode_t mode=(fp.st_mode&S_IFMT);//判断文件类型
	if(strcmp(argv[1],"-n")==0||strcmp(argv[1],"-l")==0)
	{
		if(mode==S_IFDIR)
		{
			fglob(argv[2],&globres);
			for(i=0;i<globres.gl_pathc;i++)
			{
				f_stat(globres.gl_pathv[i],&fp);
				fmode(argv[1],globres.gl_pathv[i],fp);
			}
		}
		else
		{
			f_stat(argv[2],&fp);
			fmode(argv[1],argv[2],fp);	
		}
	}
	//printf("%s",perm);
	return 0;	
}

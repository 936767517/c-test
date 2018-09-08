#include <sys/stat.h>
#include <sys/types.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <glob.h>
#include <pwd.h>
#include <grp.h>
#define TIMESTRSIZE 1024
int  f_mode(char *fname,int n)
{
	struct stat fp;
	struct passwd *pwdline;
	struct group *gidline;
	if(stat(fname,&fp)<0)
	{
		perror("stat()");
		return -1;
	}
	char perm[13]="----------.";
	mode_t mode=(fp.st_mode&S_IFMT);//判断文件类型
	switch(mode)
	{
		case S_IFSOCK:*(perm+0)='s';break;
		case S_IFLNK:*(perm+0)='l';break;
		case S_IFREG:*(perm+0)='-';break;
		case S_IFBLK:*(perm+0)='b';break;
		case S_IFDIR:*(perm+0)='d';break;
		case S_IFCHR:*(perm+0)='c';break;
		case S_IFIFO:*(perm+0)='p';break;
		default:break;
	}
	mode=(fp.st_mode&S_IRWXU);//判断权限
	if(mode&S_IRUSR)
		*(perm+1)='r';
	if(mode&S_IWUSR)
		*(perm+2)='w';
	if(mode&S_IXUSR)
	{
		if(fp.st_mode&S_ISUID)
			*(perm+3)='S';
		*(perm+3)='x';
	}
	else
	{
		if(fp.st_mode&S_ISUID)
			*(perm+3)='s';
	}
	mode=(fp.st_mode&S_IRWXG);//判断权限
	if(mode&S_IRGRP)
		*(perm+4)='r';
	if(mode&S_IWGRP)
		*(perm+5)='w';
	if(mode&S_IXGRP)
	{
		if(fp.st_mode&S_ISGID)
			*(perm+6)='S';
		*(perm+6)='x';
	}
	else
	{
		if(fp.st_mode&S_ISGID)
			*(perm+6)='s';
	}
	mode=(fp.st_mode&S_IRWXO);//判断权限
	if(mode&S_IROTH)
		*(perm+7)='r';
	if(mode&S_IWOTH)
		*(perm+8)='w';

	if(mode&S_IXOTH)
		*(perm+9)='x';
	if(fp.st_mode&S_ISVTX)
		*(perm+9)='t';
	printf("%s",perm);
	if(n==2)//连接数  uid gid
	{
		printf("%2d%2d%2d",fp.st_nlink,fp.st_uid,fp.st_gid);
	}
	if(n==1)//连接数  uname gname
	{
		pwdline=getpwuid(fp.st_uid);
		gidline=getgrgid(fp.st_gid);
		printf("%2d %s %s",fp.st_nlink,pwdline->pw_name,gidline->gr_name);
	}
	printf(" %d",fp.st_size);
	struct tm *tm;//时间
	char timestr[TIMESTRSIZE];
	tm=localtime(&fp.st_mtime);
	strftime(timestr,TIMESTRSIZE,"%b %d %H:%m",tm);
	printf(" %s",timestr);
}

int main(int argc,char **argv)
{
	int i=0,a=0,n=0,d=0;
	int arr[1024];
	int ch;
	int j;
	char path[1024];
	char nextpath[1024];
	int num=0;
	struct stat fp;
	glob_t globres;
	while(1)
	{
		ch=getopt(argc,argv,"-linad");//参数
		if(ch<0)
		{
			break;		
		}
		switch(ch)
		{
			case 1:arr[num]=optind-1;num++;break;
			case 'l':
				   if(n!=2)
				   	n=1;
				   break;
			case 'n':n=2;break;
			case 'a':a=1;break;
			case 'i':i=1;break;
			case 'd':d=1;break;
			default :break;
		}
	}
	if(num==0)//没有指定目录
	{
		printf("optind=%d\n",optind);
		argv[optind]=getcwd(path,1024);
		arr[num]=optind;
		num++;
	}
	while(num>0)//指定
	{
		num--;
		strncpy(path,argv[arr[num]],1024);
		if(stat(path,&fp)<0)
		{
			perror("stat()");
			return -1;
		}
		mode_t mode=(fp.st_mode&S_IFMT);//判断文件类型
		if(mode==S_IFDIR)//目录文件
		{
			if(d==1)//有d
			{
				if(i==1)//有i
				{
					printf("%d ",fp.st_ino);
				}
				if(n>0)//l  n
				{
					f_mode(path,n);
				}
				printf("%s\n",path);
			}
			else//没有d
			{
				printf("%s:\n",path);
				strncpy(nextpath,path,1024);//非隐藏
				strncat(nextpath,"/*",1024);
				glob(nextpath,0,NULL,&globres);
				if(a==1)//隐藏
				{	
					strncpy(nextpath,path,1024);
					strncat(nextpath,"/.*",1024);
					glob(nextpath,GLOB_APPEND,NULL,&globres);
				}
				for(j=0;j<globres.gl_pathc;j++)
				{
					if(i==1)//i
					{
						if(stat(globres.gl_pathv[i],&fp)<0)
						{
							perror("stat()");
							return -1;
						}
						printf("%d ",fp.st_ino);
					}
					if(n>0)//l n
					{
						f_mode(globres.gl_pathv[j],n);
					}
					printf(" %s\n",globres.gl_pathv[j]);
				}
			}
		}
		else//文件
		{
			if(i==1)//i
			{
				printf("%d ",fp.st_ino);
			}
			if(n>0)//n
			{
				f_mode(path,n);
			}
			printf("%s\n",path);
		}
	}

	return 0;
}


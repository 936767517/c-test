#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>
#include "proto.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "medialib.h"


#define PATHSIZE 200
#define BUFSIZE	1024

struct mytbf_st{
	int token;
	int cps;
};

struct mlib_chn_context_s
{
	chnid_t chnid;
	char *desc;
	struct mytbf_st *tbf;
	glob_t globres;
	int curr;
	int fd;
	off_t offset;
};

static struct mlib_chn_context_s mlib_job[NR_CHN];

//int main(void)
int mlib_getchnlist(struct mlib_chn_st **listptr, int *listsize)
{
	int i,j;
	int fd_desc;
	int ret;
	char path[PATHSIZE];
	char buf[BUFSIZE] = {};
	
	*listptr = malloc(sizeof(**listptr)*NR_CHN);
	*listsize = NR_CHN;

	for(i = 0; i<NR_CHN; i++)
	{
		mlib_job[i].chnid = i+1;			//初始化chnid
		(*listptr)[i].chnid = i+1;
		sprintf(path, "/media/%d", i+1);
		strcat(path,"/*");
		glob(path, 0, NULL, &mlib_job[i].globres);   //初始化globres
		mlib_job[i].curr = 0;			//初始化i频道的curr
		mlib_job[i].fd = open(mlib_job[i].globres.gl_pathv[mlib_job[i].curr], O_RDONLY);	//初始化fd

	}


	for(i=0; i<NR_CHN; i++)
	{
		for(j = 0; j<mlib_job[i].globres.gl_pathc; j++)
		{
			sprintf(path, "/media/%d/desc.txt", i+1);
			if(strcmp(mlib_job[i].globres.gl_pathv[j], path) == 0)		//找到频道的描述文件
			{
				memset(buf, '\0', BUFSIZE);
				fd_desc = open(mlib_job[i].globres.gl_pathv[j], O_RDONLY);
				if(fd_desc < 0)
				{
					perror("open()");
					exit(1);
				}
				ret = read(fd_desc, buf, BUFSIZE);
				if(ret < 0)
				{
					perror("read()");
					exit(1);
				}

				/*mlib_job[i].desc = malloc(ret);			//后面要free
				strncpy(mlib_job[i].desc, buf, ret);	//初始化desc; malloc加strcpy防止栈空间重写
				mlib_job[i].desc[ret-1] = '\0';*/

				(*listptr)[i].desc = malloc(ret);
				strncpy((*listptr)[i].desc, buf, ret);			
				(*listptr)[i].desc[ret-1] = '\0';

			}
		}
	}



}

struct msg_channel_st mlib_getchndata(int i)
{
	struct msg_channel_st channel_data;
	int pos = 0;
	int len;
	int size = MAX_DATA;
	char path[PATHSIZE];

	channel_data.chnid = i;
	printf("%d\n", i);
	while(1)
	{

		len = read(mlib_job[i-1].fd, channel_data.data+pos, size);
		if(len < size)
		{
			size -= len;
			pos += len;
		}
		else if(len == size)
		{
			break;
		}
		if(len == 0)
		{
			mlib_job[i-1].curr += 1;
			sprintf(path, "/media/%d/desc.txt", i);
			if(strcmp(mlib_job[i-1].globres.gl_pathv[mlib_job[i-1].curr], path) == 0)
			{
				mlib_job[i-1].curr += 1;
			}
			mlib_job[i-1].fd = open(mlib_job[i-1].globres.gl_pathv[mlib_job[i-1].curr], O_RDONLY);
		}
	}

	return channel_data;
}







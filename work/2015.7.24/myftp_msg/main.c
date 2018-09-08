#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "proto1.h"
enum
{
	STAT_RCV=1;
	STAT_SND;
	STAT_EX;
	STAT_QUIT;
}
int main()
{
	key_y key;
	msg_path_t mpath;
	msg_data_t mdata;
	int msgid;
	int fd;
	int res;
	int stat=STAT_RCV;
	key=ftok(KEYPATH,KEYPROJ);
	if(key<0)
	{
		perror("ftok()");
		return -1;
	}
	msgid=msgget(key,0);
	if(msgid<0)
	{
		perror("msgget()");
		return -1;
	}
	while(1)
	{
		swith(stat)
		{
			case 'STAT_RCV':
				if(msgrcv(msgid,&mpath,sizeof(mpath)-sizeof(long),0,0)<0)
				{
					perror("msgrcv()");
					return -1;
				}
				stat =STAT_SND;
				break;
			case 'STAT_SND':
				fd=open(mpath.path,O_RDONLY);
				if(fd<0)
				{
					perror("open()");
					return -1;
				}
				res=read(fd,mdata.data,DATASIZE);
				if(res<0)
				{

					perror("read()");
					return -1'
				}
				break;
			case 'STAT_EX':
				stat=STAT_QUIT;
				break;
			case 'STAT_QUIT':
				break;
		}
	}

	return 0;
}

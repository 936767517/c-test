#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<errno.h>

#include "proto.h"
enum
{
	STAT_RCV=1,
	STAT_READ,
	STAT_SND,
	STAT_EX,
	STAT_QUIT
};
int main()
{
	key_t key;
	msg_path_t mpath;
	msg_data_t mdata;
	msg_err_t 	merr;
	//union msg_s2c_un  msg_snd;
	msg_eot_t  	meot;
	int msgid;
	int fd;
	int res=0;
	int pos=0;
	int num=0;
	int stat=STAT_RCV;
	key=ftok(KEYPATH,KEYPROJ);
	if(key<0)
	{
		perror("ftok()");
		return -1;
	}
	msgid=msgget(key,IPC_CREAT|0600);
	//msgid=msgget(key,0);
	if(msgid<0)
	{
		perror("msgget()");
		return -1;
	}
	while(1)
	{
		switch(stat)
		{
			case STAT_RCV:
				num=sizeof(mpath)-sizeof(long);
				if(msgrcv(msgid,&mpath,num,0,0)<0)
				{	
					perror("msgrcv(jj)");
					if(errno==EAGAIN||errno==EINTR)
					{
						continue;
					}
					merr.err=errno;
					stat=STAT_EX;
					break;
				}
				fd=open(mpath.path,O_RDONLY);
				if(fd<0)
				{
					perror("open()");
					merr.err=errno;
					stat=STAT_EX;
					break;
				}
					stat =STAT_READ;
				
				break;
			case STAT_READ:
					res=read(fd,mdata.data,DATASIZE);
					if(res<0)
					{
						perror("read()");
						if(errno==EAGAIN||errno==EINTR)
						{
							continue;
						}
						merr.err=errno;
						stat=STAT_EX;
					break;
					}
					pos+=res;
					stat=STAT_SND;
				break;
			case STAT_SND:
					if(res==0)
					{
						meot.mtype=MSG_EOT;
						if(msgsnd(msgid,&meot,sizeof(meot)-sizeof(long),0)<0)		
						{
							merr.err=errno;
							stat=STAT_EX;
					break;
						}
						stat=STAT_QUIT;
					}
					else
					{
						mdata.mtype=MSG_DATA;
						mdata.datalen=res;
						if(msgsnd(msgid,&mdata,sizeof(mdata)-sizeof(long),0)<0)
						{
							merr.err=errno;	
							stat=STAT_EX;
					break;
						}
						stat=STAT_READ;
					}
				break;
			case STAT_EX:
				stat=STAT_QUIT;
				merr.mtype=MSG_ERR;
				if(msgsnd(msgid,&merr,sizeof(merr)-sizeof(long),0)<0)
				{
					merr.err=errno;
					stat=STAT_EX;
					
				}
				break;
			case STAT_QUIT:
				//msgctl(msgid,IPC_RMID,NULL);
				close(fd);
				return 0;
				break;
		}
	}

	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<errno.h>

#include "proto.h"

#define FILEPATH  "/etc/services"
enum{
	STAT_SND=1,
	STAT_RCV,
	STAT_EX,
	STAT_OUT,
	STAT_QUIT,
};

int main()
{
	key_t key;
	msg_path_t mpath;
	int msgid;
	int res=0;
	int stat=STAT_SND;
	int len=0;
	int val=0;
	int pos=0;
	union msg_s2c_un msg_rcv;
	key=ftok(KEYPATH,KEYPROJ);
	if(key<0)
	{
		perror("ftok()");
		return 1;
	}
	msgid=msgget(key,IPC_CREAT|0600);
	//msgid=msgget(key,0);
	if(msgid<0)
	{
		perror("msgget()");
		return -1;
	}
	mpath.mtype=MSG_PATH;
	strcpy(mpath.path,FILEPATH);
	while(1)
	{
		switch(stat)
		{
			case STAT_SND:
				res=msgsnd(msgid,&mpath,sizeof(mpath)-sizeof(long),0);
				if(res<0)
				{
					if(errno==EAGAIN)
					{
						continue;
					}
					perror("msgsnd()");
					return -1;
				}
				stat=STAT_RCV;
		   		break;	  
			case STAT_RCV:
				len=msgrcv(msgid,&msg_rcv,(sizeof(msg_rcv)-sizeof(long)),0,0);
				if(len<0)
				{
					if(errno==EAGAIN)
					{
						continue;
					}
					perror("msgrcv()");
					stat=STAT_EX;
					break;
				}
				else
				{
					if(msg_rcv.mtype==MSG_ERR)
					{
						fprintf(stderr,"msgrcv():%s\n",strerror(msg_rcv.errmsg.err));
						stat=STAT_EX;
					}
					if(msg_rcv.mtype==MSG_EOT)
					{
						stat=STAT_QUIT;
					}
					if(msg_rcv.mtype==MSG_DATA)
					{
						stat=STAT_OUT;
					}
				}
				break;
			case STAT_OUT:
				sleep(1);
				do
				{
					pos=write(1,msg_rcv.datamsg.data,msg_rcv.datamsg.datalen);
					if(pos<0)
					{
						if(errno==EAGAIN||errno==EINTR)
						{
							continue;
						}
						perror("write()");
						return -1;
					}
					val+=pos;
				}while(val<msg_rcv.datamsg.datalen);
				stat=STAT_RCV;
				break;
			case STAT_EX:
				stat=STAT_QUIT;
			break;
			case STAT_QUIT:
			msgctl(msgid,IPC_RMID,NULL);
			return 0;
			break;
			default:
			return -1;	
		}
	}
	return 0;
}

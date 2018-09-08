#include "proto1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILEPATH  "/etc/passwd"
enum{
	STAT_SND=1;
	STAT_RCV;
	STAT_EX;
	STAT_QUIT;
}

int main()
{
	key_t key;
	msg_path_t mpath;
	int msgid;
	int res=0;
	int stat=STAT_SND;
	int len=0;
	int val=0;
	union msg_s2c_un msg_rcv;
	key=ftok(KEYPATH,KEYPROJ);
	if(key<0)
	{
		perror("ftok()");
		return 1;
	}
	msgid=msgget(key,IPC_CREAT|0600);
	if(msgid<0)
	{
		perror("msgget()");
		return -1;
	}
	mpath.mtype=MSG_PATH;
	strcpy(&mpath.path,FILEPATH);
	while(1)
	{
		switch(stat)
		{
			case 'STAT_SND':
				res=msgsnd(msgid,&mpath,sizeof(mpath)-sizeof(long),0);
				if(res<0)
				{
					if(res==EAGAIN)
					{
						continue;
					}
					perror("msgsnd()");
					return -1;
				}
				stat=STAT_RCV;
		   		break;	  
			case 'STAT_RCV':
				len=msgrcv(msgid,&msg_rcv,sizeof(msg_rcv)-sizeof(long),0,0);
				if(len<0)
				{
					if(len==EAGAIN)
					{
						continue;
					}
					perror("msgrcv()");
					return -1;
				}
				if(msg_rcv.mtype==MSG_ERR)
				{
					fprintf(stderr,"msgrcv():%s\n",strerror(msg_rcv.errmsg.errno));
					stat=STAT_EX;
				}
				if(msg_rcv.mtype==MSG_EOT)
				{
					stat=STAT_QUIT;
				}
				if(msg_rcv.mtype==MSG_DATA)
				{
					do
					{
					pos=write(1,msg_rcv.datamsg.data,len);
					if(pos<0)
					{
						if(pos==EAGAIN||pos==EINTR)
						{
							continue;
						}
						perror("write()");
						return -1;
					}
					val+=pos;
					}while(val!=len);
				}
				break;
			case 'STAT_EX':
				stat=STAT_QUIT;
			break;
			case 'STAT_QUIT':
			msgctl(msgid,IPC_RMID,NULL);
			break;
			default:
			return -1;	
		}
	}
	return 0;
}

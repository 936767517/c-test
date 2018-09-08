#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>

#include "proto.h"

#define FILEPATH  "proto.h"
enum{
	STAT_SND=1,
	STAT_RCV,
	STAT_EX,
	STAT_OUT,
	STAT_QUIT,
};

int main(int argc,char** argv)
{
	if(argc<2)
	{
		fprintf(stderr,"Usage...\n");
		return -1;
	}
	int sd;
	struct sockaddr_in laddr,raddr;
	msg_path_t mpath;
	int res=0;
	int stat=STAT_SND;
	int len=0;
	int val=0;
	int pos=0;
	socklen_t raddr_len;
	union msg_s2c_un msg_rcv;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	if(sd<0)
	{
		perror("socket()");
		return -1;
	}
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(SEDPORT));
	inet_pton(AF_INET,"127.0.0.1",&laddr.sin_addr.s_addr);
	if(bind(sd,(void*)&laddr,sizeof(laddr))<0)
	{
		perror("bind()");
		return -1;
	}
	while(1)
	{
		switch(stat)
		{
			case STAT_SND:
				mpath.mtype=MSG_PATH;
				strcpy(mpath.path,FILEPATH);
				raddr.sin_family=AF_INET;
				raddr.sin_port=htons(atoi(RCVPORT));
				inet_pton(AF_INET,argv[1],&raddr.sin_addr.s_addr);
				if(sendto(sd,&mpath,sizeof(mpath),0,(void *)&raddr,sizeof(raddr))<0)
				{
					perror("sendto()");
					return -1;
				}
				stat=STAT_RCV;
		   		break;	  
			case STAT_RCV:					
					if(recvfrom(sd,&msg_rcv,sizeof(msg_rcv),0,(void *)&raddr,&raddr_len)<0)
					{
						perror("recvfrom()");
						return -1;
					}
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
				break;
			case STAT_OUT:
				do
				{
					pos=write(1,msg_rcv.datamsg.data,msg_rcv.datamsg.datalen);
					//fflush(NULL);
					printf("pos==\n");
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
				}while(val<msg_rcv.datamsg.datalen);
				stat=STAT_RCV;
				break;
			case STAT_EX:
				stat=STAT_QUIT;
			break;
			case STAT_QUIT:
			close(sd);
			return 0;
			break;
			default:
			return -1;	
		}
	}
	return 0;
}

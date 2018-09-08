#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include<arpa/inet.h>
#include <sys/socket.h>
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
	int stat=STAT_RCV;
	int sd;
	int fd;
	int res=0,pos=0;
	struct sockaddr_in laddr,raddr;
	socklen_t raddr_len;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	if(sd<0)
	{
		perror("socket()");
		exit(1);
	}
	laddr.sin_family = AF_INET;
	laddr.sin_port =htons(atoi(RCVPORT));
	inet_pton(AF_INET,"172.16.60.193",&laddr.sin_addr.s_addr);
	if(bind(sd,(void *)&laddr,sizeof(laddr))<0)
	{
		perror("bind()");
		exit(1);
	}
	while(1)
	{
		switch(stat)
		{
			case STAT_RCV:
				if(recvfrom(sd,&mpath,sizeof(mpath),0,(void *)&raddr,&raddr_len)<0)
				{					
					merr.err=errno;
					stat=STAT_EX;
					break;
				}
				printf("%s\n",mpath.path);
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
					//lseek(fd,pos,SEEK_SET);
					res=read(fd,mdata.data,DATASIZE);
					if(res<0)
					{
						perror("read()");
						if(res==EAGAIN||res==EINTR)
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
				raddr.sin_family=AF_INET;
				raddr.sin_port=htons(atoi(RCVPORT));
				raddr.sin_addr=raddr.sin_addr;
				//inet_pton(AF_INET,"127.0.0.1",&raddr.sin_addr.s_addr);
					if(res==0)
					{
						meot.mtype=MSG_EOT;
						//if(sendto(sd,&meot,sizeof(meot),0,(void *)&raddr,sizeof(raddr))<0)		
						if(sendto(sd,&meot,sizeof(meot),0,(void *)&raddr,raddr_len)<0)		
						{
							perror("sendtoeot()");
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
						//sleep(1);
						if(res=sendto(sd,&mdata,sizeof(mdata),0,(void *)&raddr,sizeof(raddr))<0)
						{
							perror("sendtodata()");
							merr.err=errno;	
							stat=STAT_EX;
							break;
						}
					printf("[%s]\n",mdata.data);
						printf("data=%d\n",res);
						stat=STAT_READ;
					}
					break;
			case STAT_EX:
					stat=STAT_QUIT;

					merr.mtype=MSG_ERR;
					if(sendto(sd,&merr,sizeof(merr),0,(void *)&raddr,sizeof(raddr))<0)
				{
					merr.err=errno;
					stat=STAT_EX;
					
				}
				break;
			case STAT_QUIT:
				//close(sd);
				close(fd);
				return 0;
				break;
		}
	}

	return 0;
}

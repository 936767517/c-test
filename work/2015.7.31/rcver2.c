#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "proto.h"

#define IPSTRSIZE		40

int main()
{
	int sd;
	struct sockaddr_in laddr,raddr;
	struct msg_list_st rbuf;	
	struct msg_list_st* p;	
	p=&rbuf;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];
	int i;
	sd = socket(AF_INET,SOCK_DGRAM,0 /*IPPROTO_UDP*/);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	struct ip_mreqn mreq;
    inet_pton(AF_INET,DEFAULT_MGROUP,&mreq.imr_multiaddr);
    inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
    mreq.imr_ifindex = if_nametoindex("eth0");

    if(setsockopt(sd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)  
    {
        perror("setsockopt()");
        exit(1);
    }

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(DEFAULT_PORT));
	inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr.s_addr);
	if(bind(sd,(void *)&laddr,sizeof(laddr)) < 0)
	{
		perror("bind()");
		exit(1);
	}

	raddr_len = sizeof(raddr);
	int res=0;

	while(1)
	{
		printf("====\n");
		if((res=recvfrom(sd,&rbuf,50,0,(void *)&raddr,&raddr_len)) < 0)
		{
			perror("recvfrom()");
			exit(1);
		}
		printf("res=%d\n",res);
		inet_ntop(AF_INET,&raddr.sin_addr.s_addr,ipstr,IPSTRSIZE);
		if(rbuf.chnid != 0)
			continue;
		else
		{

			printf("[%d]\n",rbuf.chnid);
			printf("[%c]\n",*(&rbuf+1*250));
			printf("[%s]\n",&rbuf+1*250+1);
		}

	}

	close(sd);


	exit(0);
}





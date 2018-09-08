#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include "proto.h"

int main(int argc ,char **argv)
{
		int sd;
		struct msg_channel_st *sbuf;
		struct sockaddr_in raddr;

		sd = socket(AF_INET,SOCK_DGRAM,0 /*IPPROTO_UDP*/);
		if(sd < 0)
		{
				perror("socket()");
				exit(1);
		}

		struct ip_mreqn mreq;
		inet_pton(AF_INET,"224.2.2.2",&mreq.imr_multiaddr);	
		inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);	
		mreq.imr_ifindex = if_nametoindex("eth0");

		if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_IF,&mreq,sizeof(mreq)) < 0)
		{
				perror("setsockopt()");
				exit(1);
		}
	while(1)
	{
		sleep(1);
		sbuf = malloc(MAX_MSG);
		memset(sbuf,'\0',sizeof(*sbuf));
		sbuf->chnid = 1;
		sprintf(sbuf->data, "sucker!");
		raddr.sin_family = AF_INET;
		raddr.sin_port = htons(atoi("1989"));
		inet_pton(AF_INET,"224.2.2.2",&raddr.sin_addr.s_addr);

		if(sendto(sd,sbuf,MAX_MSG,0,\
					(void *)&raddr,sizeof(raddr)) < 0)
		{
				perror("sendto()");
				exit(1);
		}
	}
		puts("ok!");

		close(sd);

		exit(0);
}


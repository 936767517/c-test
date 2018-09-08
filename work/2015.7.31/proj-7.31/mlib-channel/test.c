#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "medialib.h"
#include "proto.h"
#include "thr_channel.h"

int main()
{
	struct mlib_chn_st *listptr;
	int listsize;
	int i;
    
	mlib_getchnlist(&listptr, &listsize);

	for(i=0; i<listsize; i++)
{

	printf("%s\n", listptr[i].desc);
}
	int sd1,sd2,sd3,sd4,sd5;

	sd1 = socket(AF_INET,SOCK_DGRAM,0);
	if(sd1 < 0)
	{
		perror("socket()");
		exit(1);
	}

	struct ip_mreqn mreq;
	inet_pton(AF_INET,DEFAULT_MGROUP,&mreq.imr_multiaddr);
	inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
	mreq.imr_ifindex = if_nametoindex("eth0");

	if(setsockopt(sd1,IPPROTO_IP,IP_MULTICAST_IF,&mreq,sizeof(mreq)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}

	sd2 = socket(AF_INET,SOCK_DGRAM,0);
	if(sd2 < 0)
	{
		perror("socket()");
		exit(1);
	}

	if(setsockopt(sd2,IPPROTO_IP,IP_MULTICAST_IF,&mreq,sizeof(mreq)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}

	thr_channel_create(1,sd1);
	thr_channel_create(2,sd2);
	thr_channel_create(3,sd1);
	thr_channel_create(4,sd2);
	thr_channel_create(5,sd1);

	while(1)
		pause();

	exit(0);
	
}

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include"proto.h"
#define BUFSIZE 1024
int main(int argc,char **argv)
{
	if(argc<2)
	{
		fprintf(stderr,"Usage...\n");
		return -1;
	}
	char buf[BUFSIZE];
	int sd;
	struct sockaddr_in raddr;
	socklen_t  raddr_len;
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
	{
		perror("scket()");
		return -1;
	}

//	bind();
	raddr_len=sizeof(raddr);
	raddr.sin_family=AF_INET;
	raddr.sin_port = htons(atoi(SERVERPORT));
	inet_pton(AF_INET,argv[1],&raddr.sin_addr);

	if(connect(sd,(void *)&raddr,raddr_len)<0)
	{
		perror("connect()");
		return -1;
	}
	

	if(recv(sd,buf,BUFSIZE,0)<0)
	{
		perror("recv()");
		return -1;
	}
	printf("%s",buf);

	close(sd);


	exit(0);
}




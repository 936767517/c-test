#include<stdio.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include<signal.h>
#include <syslog.h>
#include<fcntl.h>
#include<unistd.h>
#include<proto.h>
//#include "server.h"
#include"thr_list.h"
#include"medialib.h"
/*
 *	-M          指定多播地址
 *	-P			指定测试用端口
 *	-F			前台调试运行
 *	-D			指定调试频道
 *	-H          显示帮助
 *
 * */

int tid;
static int daemonize(void)
{
	pid_t pid;
	int fd;
	pid=fork();
	if(pid<0)
	{
		perror("fork()");
		syslog(LOG_ERR,"fork():%s",strerror(errno));
		return -1;
	}
	if(pid>0)
		return 0;
	fd=open("/dev/null",O_RDWR);
	if(fd<0)
	{
		perror("open()");
		syslog(LOG_WARNING,"open():%s",strerror(errno));
	}
	else
	{
		dup2(fd,0);
		dup2(fd,1);
		dup2(fd,2);
		if(fd>2)
		{
			close(fd);
		}
	}
	setsid();
	chdir("/");
	umask(0);
	return 0;
}

void daemon_exit(int s)
{
	thr_list_destroy(tid);
	thr_channel_destroy();

	closelog();
	exit(0);
}
int main(int argc,char **argv)
{
	struct mlib_chn_st *listptr;
	int listsize;
	int sd;
	int i;
	struct sigaction sa;

	openlog("projectipV4()",LOG_PID,LOG_DAEMON);
	sa.sa_handler = daemon_exit;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask,SIGQUIT);
	sigaddset(&sa.sa_mask,SIGTERM);
	sigaddset(&sa.sa_mask,SIGINT);
	sa.sa_flag = 0;
	sigaction(SIGINT,&sa,NULL);
	sigaction(SIGTERM,&sa,NULL);
	sigaction(SIGQUIT,&sa,NULL);

	if(daemonize())
	{
		syslog(LOG_ERR,"deamonize() failed");
		exit(0);
	}
	else
	{
		syslog(LOG_INFO,"daemonize() sucessed");
	}
	/* conf处理	*/

	/* socket 初始化 */
	sd=socket(AF_INET,SOCK_DGRAM,0);
	if(sd<0)
	{
		perror("socket()");
		exit(1);
	}
	struct ip_mreqn mreq;
	inet_pton(AF_INET,DEFAULT_MGROUP,&mreq.imr_multiaddr);
	inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
	mreq.imr_ifindex = if_nametoindex("eth0");

	if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_IF,&mreq,sizeof(mreq))<0)
	{
		perror("setsocktopt()");
		return -1;
	}

	/* 获取频道列表（从media中获取）*/
	if(mlib_getchnlist(&listptr,&listsize) < 0)
	{
		//syslog();
		fprintf(stderr,"mlib_getchnlist()err\n");
		return -1;
	}


	/* 创建thr_list	*/
	tid=thr_list_create(sd);
	/*if error*/
	if(tid<0)
	{
		syslog(LOG_ERR,"thr_list_create()failed");
		return -1;
	}
	else
	{
		syslog(LOG_INFO,"thr_list_create()successed");
	}


	/* 创建thr_channel*/
	/*1:200   10:200   200:200*/

	for(i = 0 ; i < listsize ; i++)
	{
		thr_channel_create(sd,i);
	}

	while(1)
		pause();

	exit(0);
}


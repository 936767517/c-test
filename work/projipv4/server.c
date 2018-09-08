#include "server.h"
/*
 *	-M          指定多播地址
 *	-P			指定测试用端口
 *	-F			前台调试运行
 *	-D			指定调试频道
 *	-H          显示帮助
 *
 * */

int main(int argc,char **argv)
{
	//struct mlib_chn_st *listptr;
	//int listsize;
	int sd;
	int i;
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

	/*if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_IF,&mreq,sizeof(mreq))<0)
	{
		perror("setsocktopt()");
		return -1;
	}*/

	/* 获取频道列表（从media中获取）*/
	/*if(mlib_getchnlist(&listptr,&listsize) < 0)
	{
		//syslog();
		fprintf(stderr,"mlib_getchnlist()err\n");
		return -1;
	}*/


	/* 创建thr_list	*/
	thr_list_create(sd,listptr,listsize);
	/*if error*/


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


#include<stdio.h>
 #include<stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include<pthread.h>
typedef uint8_t chnid_t;
#define DEFAULT_MGROUP      "224.2.2.5"
#define DEFAULT_PORT        "1989"
#define MAX_MSG             (65536-60-8)
#define CHNID_LIST          0
struct mlib_chn_st{
	chnid_t chnid;
	char *desc;
};
struct msg_channel_st {
	chnid_t chnid;
	uint8_t data[MAX_MSG];
}__attribute__((packed));

struct list_entry_st
{
	chnid_t chnid;          /*MUST BE [MINCHNID,MAXCHNID]*/
//	len;
	uint8_t desc[1];
}__attribute__((packed));

struct msg_list_st
{
	chnid_t chnid; 			/* MSUT BE CHNID_LIST */
	struct list_entry_st entry[1];
}__attribute__((packed));

static int send_message(int sd,struct msg_list_st *list)
{
	struct sockaddr_in raddr;
	int res;
	raddr.sin_family=AF_INET;
	raddr.sin_port=htons(atoi(DEFAULT_PORT));
	inet_pton(AF_INET,DEFAULT_MGROUP,&raddr.sin_addr.s_addr);
	
	res=sendto(sd,list,MAX_MSG,0,(void *)&raddr,sizeof(raddr));
	printf("[%d]\n",list->chnid);
	printf("[%s]\n",(list+2));
	if(res<0)
	{
		perror("sendto()");
		return -1;
	}
	printf("res=%d\n",res);
	return res;
}

int mlib_getchnlist(struct mlib_chn_st **listptr,int *listsize)
{
	struct mlib_chn_st *ptr;
	struct mlib_chn_st n1;
	struct mlib_chn_st n2;
	n1.chnid='1';
	n1.desc="abcde";
	n2.chnid='2';
	n2.desc="fghijk";
	ptr=malloc(sizeof(n1)+sizeof(n2));
	if(ptr==NULL)
	{
		perror("malloc()");
		return -1;
	}
	ptr[0].chnid=n1.chnid;
	ptr[0].desc=malloc(strlen(n1.desc));
	strcpy(ptr[0].desc,n1.desc);
	ptr[1].chnid=n2.chnid;
	ptr[1].desc=n2.desc;
	*listptr = ptr;
	*listsize=2;
	return 0;
}
static void* thread_list_work(void *p)
{
		int sd=*(int*)p;
		struct mlib_chn_st *listptr;
		int listsize;
		struct msg_list_st *list;
		struct list_entry_st *listdesc;
		int i;
		int pos=0;
		int num;
		while(1)
		{
			pos=0;
		 if(mlib_getchnlist(&listptr,&listsize)<0)
		 {
		 	fprintf(stderr,"mlib_getchnlist() is err\n");
			pthread_exit(NULL);
		 }
		 list=malloc(MAX_MSG);
		 if(list==NULL)
		 {
		 	perror("malloc()");
			pthread_exit(NULL);
		 }
		 	memset(list,'\0',MAX_MSG);
		 for(i=0;i<listsize;i++)
		 {
			 num=strlen(listptr[i].desc);
			list->chnid=CHNID_LIST;
			pos=pos+1;
			memcpy(list+pos,&(listptr[i].chnid),1);
			printf("[%c]\n",*(list+1+250));
			pos=pos+1;
			memcpy(list+pos,listptr[i].desc,num+1);
			pos=pos+246;
			memcpy(list+pos,"\n \0",2);
			printf("[%s]",(list+2+250));
			pos=pos+2;
			printf("******\n");
				
		 }
		// printf("%d\n",list->chnid);
		
			 printf("=================\n");
		 send_message(sd,list);
		 sleep(1);
		}
		pthread_exit(NULL);
}
int  thr_list_create(int sd)
{
	pthread_t  pid;
	pthread_create(&pid,NULL,thread_list_work,(void *)&sd);
	if(pid<0)
	{
		perror("pthread_create()");
		return -1;
	}
	while(1)
	{
		pthread_join(pid,NULL);
	}
	return pid;
} 

int  thr_list_destroy( int pid)
{
	pthread_cancel(pid);
	pthread_join(pid,NULL);
	return 0;
}
int main()
{	
	int sd;	
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

	thr_list_create(sd);
	return 0;
}

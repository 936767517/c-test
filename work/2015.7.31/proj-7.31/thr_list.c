#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include<proto.h>
/*typedef uint8_t chnid_t;
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

*/
static int send_message(int sd,struct msg_channel_st *list)
{
	struct sockaddr_in raddr;
	int res;
	raddr.sin_family=AF_INET;
	raddr.sin_port=htons(atoi(DEFAULT_PORT));
	inet_pton(AF_INET,DEFAULT_MGROUP,&raddr.sin_addr.s_addr);
	
	res=sendto(sd,list,MAX_MSG,0,(void *)&raddr,sizeof(raddr));
	if(res<0)
	{
		perror("sendto()");
		return -1;
	}
	return res;
}

static void* thread_list_work(void *p)
{
		int sd=*(int*)p;
		struct mlib_chn_st *listptr;
		int listsize;
		struct msg_channel_st list;
		int i;
		int pos=0;
		while(1)
		{
			pos=0;
			if(mlib_getchnlist(&listptr,&listsize)<0)
			{
				fprintf(stderr,"mlib_getchnlist() is err\n");
				pthread_exit(NULL);
			}
			memset(&list,'\0',MAX_MSG);
			for(i=0;i<listsize;i++)
			{
				list.chnid=CHNID_LIST;
				list.data[pos]=listptr[i].chnid;
				pos=pos+1;
				list.data[pos]=':';
				pos=pos+1;
				strcpy(list.data+pos,listptr[i].desc);
				pos+=245;
				list.data[pos]='\n';
				list.data[pos+1]='\0';
				pos+=2;
		 }
		 send_message(sd,&list);
		 sleep(1);
		}
		pthread_exit(NULL);
}
int  thr_list_create(int sd)
{
	pthread_t  tid;
	pthread_create(&tid,NULL,thread_list_work,(void *)&sd);
	if(tid<0)
	{
		perror("pthread_create()");
		return -1;
	}
	while(1)
	{
		pause();
	}
	return tid;
} 

int  thr_list_destroy( int tid)
{
	pthread_cancel(pid);
	pthread_join(tid,NULL);
	return 0;
}

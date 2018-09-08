#include"thr_list.h"
#include"medialib.h"
#include"server.h"
#include"proto.h"
static int send_message(int sd,struct msg_list_st *list)
{
	struct sockaddr_in raddr;
	int res;
	raddr.sin_family=AF_INET;
	raddr.sin_port=htons(atoi(DEFAULT_PORT));
	inet_pton(AF_INET,DEFAULT_MGROUP,&raddr.sin_addr.s_addr);
	
	res=sendto(sd,list,sizeof(*list),0,(void *)&raddr,sizeof(raddr));
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
		struct list_entry_st *listdesc;
		struct msg_list_st 	*list;
		int i;
		int size=0;
		int num=0;
		while(1)
		{
		 if(mlib_getchnlist(&listptr,&listsize)<0)
		 {
		 	fprintf(stderr,"mlib_getchnlist() is err\n");
			pthread_exit(NULL);
		 }
		 size=sizeof(*list);
		 list=malloc(size);
		 if(list==NULL)
		 {
		 	perror("malloc()");
			pthread_exit(NULL);
		 }
		 for(i=0;i<listsize;i++)
		 {
			 num=strlen(listptr[i].desc)+8;
			 size+=num;
			 if(size>MAX_MSG)
			 {
				fprintf(stderr,"desc is too long\n");
			 	break;
			 }
			 list=realloc(list,size);
			 if(list ==NULL)
			 {
				 free(list);
				 perror("realloc()");
				pthread_exit(NULL);
			 }
			 memset(list,'\0',size);
			 list->chnid=CHNID_LIST;
			 list->entry[i].chnid=listptr[i].chnid;
			 strcpy(list->entry[i].desc,listptr[i].desc);
		 }
		 send_message(sd,list);
		 free(list);
		}
		pthread_exit(NULL);
}
int  thr_list_create(int sd)
{
	pthread_t  pid;
	//struct node data;
	//data.desc =*pos;
	//data.size=listsize;
	thread_create(&pid,NULL,thread_list_work,(void *)&sd);
	if(pid<0)
	{
		perror("pthread_create()");
		return -1;
	}
	while(1)
		pthread_join(pid,NULL);
	return pid;
} 

int  thr_list_destroy( int pid)
{
	pthread_cancle(pid);
	pthread_join(pid);
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

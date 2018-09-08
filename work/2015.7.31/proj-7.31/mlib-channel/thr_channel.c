#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "proto.h"
#include "thr_channel.h"
#include "medialib.h"


typedef struct channel_struc
{
	int channel_num;
	int channel_sd;
}*mychannel;

static pthread_t channel_tid[MAXTHREAD];
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;

void *channel_func(void *p);

int thr_channel_create(int mem,int sd)
{
    pthread_t tid;
	int err;
	mychannel which_channel;

	pthread_mutex_lock(&mut_job);

	which_channel = malloc(sizeof(*which_channel));
	if(which_channel == NULL)
	{
		return -1;
	}

	which_channel->channel_num = mem;
	which_channel->channel_sd =sd;

	if(channel_tid[mem] > 0)
	{
		fprintf(stderr,"Channel %d is already in use.\n",mem);
	}

	err = pthread_create(&tid,NULL,channel_func,(void *)which_channel);
	if(err)
	{
		fprintf(stderr,"pthread_create():%s\n",strerror(err));
		return -2;
	}

	channel_tid[mem] = tid; 

	pthread_mutex_unlock(&mut_job);

	return mem;
}


void *channel_func(void *p)
{
	mychannel channel_data = p;

	struct msg_channel_st send_channel_data;
	struct sockaddr_in saddr;



	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(atoi(DEFAULT_PORT));
	inet_pton(AF_INET,DEFAULT_MGROUP,&saddr.sin_addr.s_addr);


	while(1)
	{
		pthread_mutex_lock(&mut_job);

		send_channel_data = mlib_getchndata(channel_data->channel_num);
		printf("%d\n",send_channel_data.chnid);

		if(sendto(channel_data->channel_sd,&send_channel_data,sizeof(send_channel_data),0,(void *)&saddr,sizeof(saddr)) < 0)
		{
			perror("sendto()");
			exit(1);
		}


		pthread_mutex_unlock(&mut_job);
		sleep(1);
	}
}

int thr_channel_destroy(int mem)
{
	if(mem < 0)
	{
		return -1;
	}

	if(pthread_cancel(channel_tid[mem]) < 0)
	{
		return -2;
	}

	if(pthread_join(channel_tid[mem],PTHREAD_CANCELED) < 0)
	{
		return -3;
	}

	channel_tid[mem] = 0;

	return 0;
}

int thr_channel_destroyall(void)
{
	int i;
	for(i =0 ; i<MAXTHREAD; i++)
	{
		if(channel_tid[i] != 0)
		{
			thr_channel_destroy;
		}
	}

	return 0;
}


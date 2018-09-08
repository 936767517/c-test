#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>
#include <termios.h>
//#include "../include/proto.h"
#include <proto.h>
#define  PIPEBUFSIZE     (1024*20)
#include "client.h"
#define IPSTRSIZE  40
#define FILEBUF    "/tmp/radio"
/*
 *	-M			指定多播地址
 *	-P			指定播放器
 *	-p			指定测试用端口
 *	-H			显示帮助
 *
 * */
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
struct termios stc;
static int sfl;
static int rcvlist = 0;
struct client_conf_st client_conf = {
				.mgroup = DEFAULT_MGROUP,
				.rcvport = DEFAULT_PORT,
				.player = DEFAULT_PLAYER
};
static uint8_t channel = 2;
typedef union msg_data_st msg_buf;

union msg_data_st
{
	chnid_t chnid;
	struct msg_channel_st chn;
	struct msg_list_st list;
};

struct write_info
{
	int sd;
	int fd;
	int pd;
};

struct chg_fd
{
	int fdr;
	int fdw;
};
static struct chg_fd chg_chn;
static struct write_info w_buf, w_pipe;
static int clearbuf = 0;
static int clearpipe = 0;
void init_keyboard()
{
	struct termios tc;

	sfl = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, sfl|O_NONBLOCK);//将io设成非阻塞

	tcgetattr(0, &tc);
	stc = tc;
	tc.c_lflag &= (~ICANON);
	tc.c_lflag &= (~ECHO);

	tcsetattr(0, TCSANOW, &tc);
}

void recover_keyboard()
{
	tcsetattr(0, TCSANOW, &stc);
	fcntl(0, F_SETFL, sfl);
}

static void channel_dis(void *p)
{
	char *tmp = p;
	printf("\033[13;2H\033[K%s\033[?25l", tmp + 1 + (channel-1)*250);
	printf("\033[0m");
}
static void *write_buf(void *p)
{
	struct msg_channel_st rbuf;
	struct sockaddr_in raddr;
	socklen_t raddr_len = sizeof(raddr);
	char ipstr[IPSTRSIZE];
	struct write_info *tmp = p;
	
	while(1)
	{
		if(recvfrom(tmp->sd, &rbuf,	MAX_MSG, 0, \
				(void *)&raddr, &raddr_len) < 0)
		{
			perror("recvfrom()");
			exit(1);
		}
		inet_ntop(AF_INET,&raddr.sin_addr.s_addr,ipstr,IPSTRSIZE);

		printf("\033[2;2H---MESSAGE FROME:%s:%d-----\033[?25l",\
				ipstr,ntohs(raddr.sin_port));
		printf("\033[0m");
		if(rbuf.chnid != 0 && rbuf.chnid != channel)
		continue;
		else if(rbuf.chnid == 0 && rcvlist == 0)
		{
			channel_dis(&rbuf);
			rcvlist = 1;
		}
		else if(rbuf.chnid == channel)
		{
			if(clearbuf == 1)
			{
				ftruncate(tmp->fd, 0);
				lseek(tmp->fd, 0, SEEK_SET);
				clearbuf = 0;
				clearpipe = 1;
			}
			int res, pos = 0;
			int val = MAX_DATA;
			printf("\033[11;2Hcurrent channel:%3d\033[?25l", channel);
			printf("\033[0m");
			while(val > 0)
			{
				res = write(tmp->fd, rbuf.data, MAX_DATA);
				if(res < 0)
				{
					if(res == EINTR || res == EAGAIN)
					continue;
					perror("write()");
					exit(1);
				}
				pos += res;
				val -= res;
			}
		}
	}
	pthread_exit(NULL);
}

static void *write_pipe(void *p)
{
	char pipebuf[PIPEBUFSIZE];
	struct write_info *tmp = p;
	int res;
//	sleep(2);
	while(1)
	{
		int val, pos = 0;
		if(clearpipe == 1)
		{
			ftruncate(tmp->fd, 0);
			ftruncate(tmp->pd, 0);
			lseek(tmp->fd, 0, SEEK_SET);
			lseek(tmp->pd, 0, SEEK_SET);
			printf("\33[12;2HPLEASE WAIT!...\033[?25l");
			printf("\033[0m");
			printf("\033[11;2Hcurrent channel:%3d\033[?25l", channel);
			printf("\033[0m");
			sleep(4);
			clearpipe = 0;
		}
		while((res = read(tmp->fd, pipebuf, PIPEBUFSIZE)) <= 0)
		{
			sleep(1);
			if(res == EINTR || res == EAGAIN || res == 0)
			continue;
			perror("read()");
			exit(1);
		}

			printf("\33[12;2H               \033[?25l");
			printf("\33[0m\n");
		while(res > 0)
		{
			val = write(tmp->pd, pipebuf, PIPEBUFSIZE);
			pos += val;
			res -= val;
		}
	}
	pthread_exit(NULL);
}
static void *change_chn(void *p)
{
	struct chg_fd *tmp = p;
	struct epoll_event ev;
	int fd_save;
	int epfd;
	char buf_t[1];

	epfd = epoll_create(10);
	if(epfd < 0)
	{
		perror("epll_create()");
		exit(1);
	}

	ev.data.fd = 0;
	epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &ev);

	while(1)
	{
		ev.events = 0;
		ev.events |= EPOLLIN;
		epoll_ctl(epfd, EPOLL_CTL_MOD, 0, &ev);

		while(epoll_wait(epfd, &ev, 1, -1)<0)
		{
			if(errno == EINTR)
				continue;
			perror("epoll_wait()");
			exit(1);
		}

		if(ev.events & EPOLLIN)
			read(0, buf_t, 1);


//		char ch = getchar();
		switch(buf_t[0])
		{
			case 'n':
				if(channel == 200)
					channel = 1;
				else
					channel++;
				clearbuf = 1;
				rcvlist = 0;
			break;
			case 'l':
				if(channel == 1)
				channel = 200;
				else
				channel--;
				clearbuf = 1;
				rcvlist = 0;
			break;
		}
	}
	pthread_exit(NULL);

}
int main(int argc,char **argv)
{
	int sd;
	int fdb,fdp;
	struct sockaddr_in raddr, laddr;
	int pd[3];
	pid_t pid;
	system("clear");
	pthread_t tid[2];
	init_keyboard();

	fdb = open(FILEBUF, \
					O_RDWR|O_TRUNC|O_CREAT|O_APPEND, 0600);
	if(fdb < 0)
	{
			perror("open()");
			exit(1);
	}
	w_buf.fd = fdb;
	chg_chn.fdw = fdb;

	fdp = open(FILEBUF, O_RDONLY);
	if(fdp < 0)
	{
			perror("open()");
			exit(1);
	}
	w_pipe.fd = fdp;
	chg_chn.fdr = fdp;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	struct ip_mreqn mreq;
	inet_pton(AF_INET,client_conf.mgroup,&mreq.imr_multiaddr);
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


	if(pipe(pd) < 0)
	{
		perror("pipe()");
		exit(1);
	}


	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	else if(pid == 0)
	{
		close(pd[1]);
		dup2(pd[0], 0);
		execl(client_conf.player, "mpg123", "-q", "-", NULL);
		perror("execl()");
		exit(0);
	}
	else
	{
		close(pd[0]);
		w_buf.sd = sd;
		w_pipe.pd = pd[1];
		int err;
		err = pthread_create(&tid[0], NULL, write_buf, (void *)(&w_buf));
		if(err)
		{
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
		err = pthread_create(&tid[1], NULL, write_pipe, (void *)(&w_pipe));
		if(err)
		{
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
		err = pthread_create(&tid[2], NULL, change_chn, (void *)(&chg_chn));
		if(err)
		{
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
		wait(NULL);

		close(sd);
		close(pd[1]);
		close(fdp);
		close(fdb);
		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
		pthread_join(tid[2],NULL);
		pthread_mutex_destroy(&mut);
		recover_keyboard();
		exit(0);
	}
	
}



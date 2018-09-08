#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <signal.h>

#define FNAME		"/tmp/out"

static FILE *fp;

static  int  deamonize(void)
{
	pid_t pid;
	int fd;

	pid = fork();
	if(pid < 0)
	{
	//	perror("fork()");
	
		syslog(LOG_ERR,"fork():%s",strerror(errno));
		return -1;
	}

	if(pid > 0)		// parent
		exit(0);

	// child
	
//	close(0);
//	close(1);
//	close(2);

	fd = open("/dev/null",O_RDWR);
	if(fd < 0)
	{
	//	perror("open()");

		syslog(LOG_WARNING,"open():%s",strerror(errno));	
	}	
	else
	{	
		dup2(fd,0);
		dup2(fd,1);
		dup2(fd,2);

		if(fd > 2)
			close(fd);
	}	

	setsid();

	chdir("/");
	umask(0);


	return 0;
}


void daemon_exit(int s)
{
	fclose(fp);
	closelog();

	exit(0);
}

int main()
{
	struct sigaction act;
	struct sigaction oact;
	int i;

	openlog("mydaemon",LOG_PID,LOG_DAEMON);

	//signal(SIGINT,daemon_exit);
	//signal(SIGQUIT,daemon_exit);
	//signal(SIGTERM,daemon_exit);
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGINT);
	sigaddset(&act.sa_mask,SIGQUIT);
	sigaddset(&act.sa_mask,SIGTERM);
	act.sa_handler=&daemon_exit;
	act.sa_flags=0;
	
	sigaction(SIGINT,&act,&oact);
	sigaction(SIGQUIT,&act,&oact);
	sigaction(SIGTERM,&act,&oact);

	if(deamonize())
	{
		syslog(LOG_ERR,"deamonize() failed.");
		exit(1);
	}
	else		
	{
		syslog(LOG_INFO,"deamonize() successed.");
	}

	/*do sth*/
	
	fp = fopen(FNAME,"w");
	if(fp == NULL)
	{
//		perror("fopen()");
		syslog(LOG_ERR,"fopen():%s",strerror(errno));
		exit(1);
	}

	syslog(LOG_DEBUG,"%s was opened.",FNAME);

	for(i = 0 ; ; i++)
	{
		fprintf(fp,"%d\n",i);
		fflush(fp);
		syslog(LOG_DEBUG,"%d was printed.",i);
		sleep(1);
	}


	exit(0);
}





#include <stdio.h>

//#include "../include/proto.h"
#include <proto.h>

#include "client.h"


/*
 *	-M			指定多播地址
 *	-P			指定播放器
 *	-p			指定测试用端口
 *	-H			显示帮助
 *
 * */

struct client_conf_st client_conf = {
				.mgroup = DEFAULT_MGROUP;
				.rcvport = DEFAULT_PORT;
				.player = DEFAULT_PLAYER

};



int main(int argc,char **argv)
{

	socket();

	pipe();


	fork();
	


}



/***************************
 * 用户态控制led的程序
 * $>./led01 /dev/ledm allon
 * $>./led01 /dev/ledm alloff
 * $>./led01 /dev/ledm on 0~3
 * $>./led01 /dev/ledm off 0~3
 * Author: zht
 * Date: 2015-08-28
 ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

//定义ioctl号, 参数是LED的编号
#define LED_TYPE	'L'
#define LED_ALL_ON	_IO(LED_TYPE, 1)
#define LED_ALL_OFF	_IO(LED_TYPE, 2)
#define LED_ON		_IOW(LED_TYPE, 3, int)
#define LED_OFF		_IOW(LED_TYPE, 4, int)

int main(int argc, char *argv[])
{
	int ret, fd, value;

	if ((argc!=3) && (argc!=4)) {
		printf("Usage: ./led01 %s allon|alloff|on|off num\n", argv[1]);
		exit(1);
	}

	//打开设备文件
	fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		printf("Cannot open %s\n", argv[1]);
		exit(1);
	}

	//执行ioctl命令
	if (argc == 4)
		value = atoi(argv[3]);

	if (strncmp(argv[2], "allon", 5)==0) 
		ret = ioctl(fd, LED_ALL_ON);
	else if (strncmp(argv[2], "alloff", 6)==0)
		ret = ioctl(fd, LED_ALL_OFF);
	else if (strncmp(argv[2], "on", 2)==0)
		ret = ioctl(fd, LED_ON, value);
	else if (strncmp(argv[2], "off", 3)==0)
		ret = ioctl(fd, LED_OFF, value);
	else {
		printf("Only support allon|alloff|on|off\n");
		exit(1);
	}

	if (ret)
		printf("%s %s failed\n", argv[2], argv[1]);
	else
		printf("%s %s succeed\n", argv[2], argv[1]);

	close(fd);
	exit(0);	
}


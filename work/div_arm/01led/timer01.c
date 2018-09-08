/*******************
 * 用户态的led_timer测试
 *******************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define LED_TYPE    'L'
#define LED_ON  _IOW(LED_TYPE, 1, struct led_info)
#define LED_OFF _IOW(LED_TYPE, 2, struct led_info)
#define LED_START _IOW(LED_TYPE, 3, struct led_info)
#define LED_STOP _IOW(LED_TYPE, 4, struct led_info)
#define LED_CHG_TIME _IOW(LED_TYPE, 5, struct led_info)

struct led_info {
	int num;
	int interval;
};

int main(int argc, void **argv)
{
	int fd, ret, value;
	struct led_info info;	
	//打开设备文件
	fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		printf("open %s error\n", argv[1]);
		exit(1);
	}
	printf("open %s\n", argv[1]);

	//根据参数执行对应行为
	if (strncmp("on", argv[2], 2) == 0) {
		info.num = atoi(argv[3]);
		ioctl(fd, LED_ON,&info);
		printf("LED ON %d...\n",atoi(argv[3]));
	}
	else if (strncmp("off", argv[2], 3) == 0) {
		info.num = atoi(argv[3]);
		ioctl(fd, LED_OFF,&info);
		printf("LED OFF %d...\n",atoi(argv[3]));
	}
	else if (strncmp("start", argv[2], 5) == 0) {
		info.num = atoi(argv[3]);
		info.interval = atoi(argv[4]);
		ioctl(fd, LED_START,&info);
		printf("LED START %d...\n",atoi(argv[3]));
	}
	else if (strncmp("stop", argv[2], 4) == 0) {
		info.num = atoi(argv[3]);
		info.interval = atoi(argv[4]);
		ioctl(fd, LED_STOP,&info);
		printf("LED STOP %d...\n",atoi(argv[3]));
	}
	else if (strncmp("change", argv[2], 6) == 0) {
		info.num = atoi(argv[3]);
		info.interval = atoi(argv[4]);
		ioctl(fd, LED_CHG_TIME,&info);
		printf("LED CHANEG %d...\n",atoi(argv[3]));
	}
	else {
		printf("Usage: %s /dev/buzz start|stop|freq|duty|high|low|up|down ...\n", argv[0]);
		exit(1);
	}

	close(fd);
	exit(0);
}	


#include <linux/fb.h>//获取显卡信息
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>//连续的三个是open需要的
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "fb_draw.h"
struct fb_st{
	int fd;//文件描述符
	unsigned long bpp;//记录每个像素点所占字节数
	char *fbp;//指向映射的那段地址空间
	struct fb_var_screeninfo var;//保存显卡的可变信息
	struct fb_fix_screeninfo fix;//保存显卡的固有信息
};

struct fb_st fb0;
int fb_open()
{
	int ret;
	fb0.fd = open("/dev/fb0", O_RDWR);//打开framebuff所对应的设备
	if(fb0.fd < 0){
		perror("open fail...");
		goto error;
	}
	ret = ioctl(fb0.fd, FBIOGET_VSCREENINFO, &fb0.var);
	if(ret == -1){
		perror("var wrong");
		goto fd_close;
	}
	ret = ioctl(fb0.fd, FBIOGET_FSCREENINFO, &fb0.fix);
	if(ret == -1){
		perror("fix wrong");
		goto fd_close;
	}

	fb0.bpp = fb0.var.bits_per_pixel / 8;
	
	fb0.fbp = mmap(NULL, fb0.fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fb0.fd, 0);//将framebuffer地址映射
	if(fb0.fbp == (void *)-1){
		perror("mmap failed");
		goto fd_close;
	}
	return 0;

error:
	return -1;
fd_close:
	close(fb0.fd);

}
void fb_close()
{
	munmap(fb0.fbp, fb0.fix.smem_len);
	close(fb0.fd);
}
/*画点*/
void fb_draw_point(int x, int y, int color)
{
	unsigned long offset;
	offset = fb0.bpp * (x+y*(fb0.var.xres + 10) );
//	memset(fb0.fbp+offset, color, fb0.bpp);
	memcpy(fb0.fbp+offset, (void *)&color, fb0.bpp);
}
int xres()
{
	return fb0.var.xres;
}
int yres()
{
	return fb0.var.yres;
}

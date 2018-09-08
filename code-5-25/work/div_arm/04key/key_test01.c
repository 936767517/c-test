#include<linux/module.h>
#include<linux/gpio.h>
#include<mach/gpio.h>
#include<linux/interrupt.h>

#define KEY1  EXYNOS4_GPX3(2)
#define KEY2  EXYNOS4_gpx3(3)

static int irq1_cnt = 0,irq2_cnt=0;

static irqreturn_t
key1_service(int irq,void* dev_id)
{
	printk("key1(%d):pressed(%d)times\n",)	
}

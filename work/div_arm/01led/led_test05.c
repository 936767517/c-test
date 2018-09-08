/**************************
 * led的测试例子4
 * 将4个led识别为1个设备，用miscdevice注册
 * 每个led有自己的定时器，一个4个timer_list
 * 用ioctl来控制led，可以实现灯的开关以及闪烁
 * Author: zht
 * Date: 2015-08-31
 **************************/
#include <linux/module.h>
#include <linux/sched.h> //jiffies
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include<linux/seq_file.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

#define LED_NUM		4

//定义ioctl命令，用户态需要把控制的灯的信息集中到结构体led_info中，然后把结构体的指针作为ioctl的第三个参数传递个内核
struct led_info {
	int num; //灯的编号0~3
	int interval; //闪烁间隔，以tick为单位
};
#define LED_TYPE	'L'
#define LED_ON	_IOW(LED_TYPE, 1, struct led_info)
#define LED_OFF	_IOW(LED_TYPE, 2, struct led_info)
#define LED_START _IOW(LED_TYPE, 3, struct led_info)
#define LED_STOP _IOW(LED_TYPE, 4, struct led_info)
#define LED_CHG_TIME _IOW(LED_TYPE, 5, struct led_info)

//定义数组，记录4个LED对应的GPIO号
static int led_gpios[LED_NUM] = {
	EXYNOS4X12_GPM4(0),
	EXYNOS4X12_GPM4(1),
	EXYNOS4X12_GPM4(2),
	EXYNOS4X12_GPM4(3),
};

//定义数组，记录每个灯当前的闪烁间隔
static int led_intervals[LED_NUM] = {0};

//定义数组，每个灯有自己的定时器
static struct timer_list led_timers[LED_NUM];

//写proc文件的读函数，返回led的信息
/*static int
led_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	//用gpio_get_value确定led当前亮还是灭
	//根据interval判断led是否闪烁
	int value,i;
	int ret=0;
	for(i=0;i<LED_NUM;i++)
	{
		value=gpio_get_value(led_gpios[i]);	
		ret+=sprintf(page+ret,"%d LED state is %d \n",i,value?on:off);
		ret+=sprintf(page+ret,"%d LED_interval is %d\n",i,led_intervals[i]);
	}
	return ret;
}*/
static int led_proc_show(struct seq_file *m,void *v)
{
	//用gpio_get_value确定led当前亮还是灭
	//根据interval判断led是否闪烁
	int value,i;
	for(i=0;i<LED_NUM;i++)
	{
		value=gpio_get_value(led_gpios[i]);	
		seq_printf(m,"%d LED state is %s \n",i,value?"off":"on");
		seq_printf(m,"%d LED_interval is %d\n",i,led_intervals[i]);
	}
	return 0;	
}
static int led_proc_open(struct inode *inode,struct file* filp)
{
	return single_open(filp,led_proc_show,NULL);
}

//写led的定时器的处理函数
//由于4个led的定时器都是翻转灯的状态，因此4个定时器可以共用同一个处理函数，但要通过参数来区分当前操作哪个灯
static void
led_timer_func(unsigned long data)
{
	//data中应该传递当前到期的是哪个led(0~3)
	int value;
	value=gpio_get_value(led_gpios[data]);
	value=(!value);
	gpio_set_value(led_gpios[data],value);
	mod_timer(&led_timers[data],jiffies+led_intervals[data]);
}

//由于只有一个设备，open函数可以默认成功

static long
led_ioctl(struct file *filp, unsigned int req, unsigned long arg)
{
	struct led_info tmp;
	if (copy_from_user(&tmp, (void *)arg, sizeof(tmp)))
		return -EFAULT;
	if (tmp.num > 3) {
		printk("Only support led 0~3\n");
		return -1;
	}
	if (tmp.interval > 10*HZ) {
		printk("Switch time between 1~10*HZ ticks\n");
		return -1;
	}

	switch (req) {
	case LED_ON:
		gpio_set_value(led_gpios[tmp.num],  0);
		break;
	case LED_OFF:
		gpio_set_value(led_gpios[tmp.num],  1);
		break;
	case LED_START:
		gpio_set_value(led_gpios[tmp.num],  0);
		led_intervals[tmp.num]=tmp.interval;
		mod_timer(&led_timers[tmp.num],jiffies+led_intervals[tmp.num]);
		break;
	case LED_STOP:
		//gpio_set_value(led_gpios[tmp.num],  1);
		//led_intervals[tmp.num] = 0;
		del_timer(&led_timers[tmp.num]);
		break;
	case LED_CHG_TIME:
		gpio_set_value(led_gpios[tmp.num],  1);
		led_intervals[tmp.num] = 0;
		del_timer(&led_timers[tmp.num]);
		
		gpio_set_value(led_gpios[tmp.num],  0);
		led_intervals[tmp.num]=tmp.interval;
		mod_timer(&led_timers[tmp.num],jiffies+led_intervals[tmp.num]);
		break;
	default:
		printk("Cannot support this commond\n");
		break;
	}
	return 0;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = led_ioctl,
};

static struct file_operations proc_fops = {
	.owner=THIS_MODULE,
	.open=led_proc_open,
	.release = single_release,
	.read=seq_read,
	.llseek=seq_lseek,
};
static struct miscdevice led_misc = {
	.minor=MISC_DYNAMIC_MINOR,
	.name ="led_timer",
	.fops=&led_fops,
};

static int __init my_init(void)
{
	int i,ret;
	struct proc_dir_entry *file;	
	//为4个GPIO申请gpio号并初始化
	//gpio_request(...);
	//s3c_gpio_cfgpin();
	//gpio_set_value(...);
	for(i=0;i<LED_NUM;i++)
	{
		gpio_request(led_gpios[i],"led_gpio");
		s3c_gpio_cfgpin(led_gpios[i],S3C_GPIO_OUTPUT);
		gpio_set_value(led_gpios[i],1);
		led_intervals[i]=0;
		setup_timer(&led_timers[i],led_timer_func,i);
	}
	//初始化4个timer_list，最后的参数应该传入led的编号
	//setup_timer(..., 0|3);
	//misc_register();
	ret=misc_register(&led_misc);
	if(ret){
		printk("Cannot register led_misc\n");
		for(i=0;i<LED_NUM;i++){
			gpio_free(led_gpios[i]);	
		}
	}
	//create_proc_read_entry();
	file=proc_create("led_state",0444,NULL,&proc_fops);
	return 0;
}

static void __exit my_exit(void)
{
	int i;
	remove_proc_entry("led_state",NULL);
	misc_deregister(&led_misc);
	for (i=0; i<LED_NUM; i++){
		led_intervals[i]=0;
		del_timer(&led_timers[i]);
		gpio_free(led_gpios[i]);
	}
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");


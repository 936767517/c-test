#include<linux/module.h>
#include<linux/fs.h>//char device
#include<linux/miscdevice.h>
#include<linux/uaccess.h>
#include<linux/proc_fs.h>

#include<linux/gpio.h>
#include<plat/gpio-cfg.h>
#include<mach/gpio.h>//gpio_num

//不用定义物理基地址，
#define LED_NUM 4

#define LED_TYPE 'L'
#define LED_ALL_ON  _IO(LED_TYPE,1)
#define LED_ALL_OFF _IO(LED_TYPE,2)
#define LED_ON _IOW(LED_TYPE,3,int)
#define LED_OFF _IOW(LED_TYPE,4,int)

static int led_gpios[LED_NUM]={
	EXYNOS4X12_GPM4(0),
	EXYNOS4X12_GPM4(1),
	EXYNOS4X12_GPM4(2),
	EXYNOS4X12_GPM4(3)
};	

static int led_proc_read(char *page,char **start,off_t off,int count,int *eof,void *data)
{
	int i,ret=0;
	ret=sprintf(page,"=====LED state====\n");
	for(i=0;i<LED_NUM;i++){
		ret+=sprintf(page+ret,"LED %d: %s\n",i,gpio_get_value(led_gpios[i])?"off":"on");
		}
		return ret;
}


static long led_ioctl(struct file* filp,unsigned int req,unsigned long arg)
{
	int i;
	if(arg>=LED_NUM){
		printk("Only support 0~3\n");
		return -1;
	}
	switch (req){
		case LED_ALL_ON:
			for(i=0;i<LED_NUM;i++)
			{
				gpio_set_value(led_gpios[i],0);	
			}
			break;
		case LED_ALL_OFF:
			for(i=0;i<LED_NUM;i++)
			{
				gpio_set_value(led_gpios[i],1);
			}
			break;
		case LED_ON:
			gpio_set_value(led_gpios[arg],0);
			break;
		case LED_OFF:
			gpio_set_value(led_gpios[arg],1);
			break;
		default:
			printk("cannot support ioctl\n");
			return -1;		
	}
	return 0;
}

static struct file_operations led_fops={
	.owner=THIS_MODULE,
		.unlocked_ioctl = led_ioctl,
};
static struct miscdevice	led_misc={
	.minor=MISC_DYNAMIC_MINOR,
	.name="ledm",
	.fops=&led_fops,
};

static int __init my_init(void)
{
	int i,ret;
	for(i=0;i<LED_NUM;i++)
	{
		gpio_request(led_gpios[i],"my_gpio");
		s3c_gpio_cfgpin(led_gpios[i],S3C_GPIO_OUTPUT);
		gpio_set_value(led_gpios[i],1);
	}
	ret=misc_register(&led_misc);
	if(ret){
		printk("cannot register led_misc\n");
		for(i=0;i<LED_NUM;i++)
		{
			gpio_free(led_gpios[i]);
		}
	}
	create_proc_read_entry("myled",0444,NULL,led_proc_read,NULL);
	return 0;
}

static void __exit my_exit(void)
{
	int i;
	remove_proc_entry("myled",NULL);
	misc_deregister(&led_misc);
	for(i=0;i<LED_NUM;i++)
	{
		gpio_free(led_gpios[i]);	
	}
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

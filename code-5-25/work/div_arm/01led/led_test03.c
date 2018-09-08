/***************************
 * led的char驱动例子3
 * 本例子支持4个LED
 * 用户态通过echo on|off来控制LED的亮灭
 * 通过proc文件来获得LED的状态(使用新的接口)
 * Author: zht
 * Date: 2015-08-27
 ***************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/proc_fs.h>
#include<linux/seq_file.h>

//定义硬件信息
#define GPIO_BASE	0x11000000
#define GPIO_SIZE	0x1000
#define GPM4CON		0x2E0
#define GPM4DAT		0x2E4

#define LED_MAJOR	60
#define LED_NUM		4	//灯的总数

//定义私有结构体
struct led_priv {
	int led_num;	//灯的编号(0~3)
	int led_state; 	//0:on; 1:off
	dev_t dev_id;
	struct cdev led_cdev;
};

//声明全局的私有结构体
static struct led_priv leds[LED_NUM];
//声明虚拟基地址
static void __iomem *vir_base;


//在proc文件中获取LED的当前状态
/*static int 
led_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int ret = 0;
	int i;
	for(i=0;i<LED_NUM;i++)
	{
		ret += sprintf(page+ret, "====LED %d(%d:%d)====\n", leds[i].led_num, MAJOR(leds[i].dev_id), MINOR(leds[i].dev_id));
		ret += sprintf(page+ret, "Now: %s\n", leds[i].led_state ? "off" : "on");
	}
	return ret;
}*/
static int led_proc_show(struct seq_file *m,void *v)
{
	
	int i;
	for(i=0;i<LED_NUM;i++)
	{
		seq_printf(m, "====LED %d(%d:%d)====\n", leds[i].led_num, MAJOR(leds[i].dev_id), MINOR(leds[i].dev_id));
		seq_printf(m, "Now: %s\n", leds[i].led_state ? "off" : "on");
	}
	return 0;
}
static int led_proc_open (struct inode *inode,struct file *filp)
{
	return single_open(filp,led_proc_show,NULL);	
}

//准备file_operations
static int 
led_open(struct inode *inode, struct file *filp)
{
	struct led_priv *tmp;
	tmp=container_of(inode->i_cdev,struct led_priv,led_cdev);
	filp->private_data=tmp;
	return 0;
}

static int
led_release(struct inode *inode, struct file *filp)
{
	return 0;
}

//对应用户态echo on|off >/dev/ledx
//如果访问一个寄存器中的某个或某些位，应该采用读--修改--写的方式
static ssize_t 
led_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	int value;
	struct led_priv* led =filp->private_data;
	char tmp[10] = {0};
	//copy_from_user(to,from,cnt)
	if (copy_from_user(tmp, buf, 4))
		return -EFAULT;
	if (strncmp(tmp, "on", 2)==0) {
		value = readl(vir_base + GPM4DAT);
		value &= ~(1 << led->led_num);
		writel(value, (vir_base + GPM4DAT));
		led->led_state = 0;
	}
	else if (strncmp(tmp, "off", 3)==0) {
		value = readl(vir_base + GPM4DAT);
		value |= (1 << led->led_num);
		writel(value, (vir_base + GPM4DAT));
		led->led_state = 1;
	}
	else {
		printk("Only suppport echo on|off\n");
		return -1;
	}
	return count;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.open = led_open,
	.release = led_release,
	.write = led_write,
};
static struct file_operations proc_fops={
	.owner=THIS_MODULE,
	.open=led_proc_open,
	.release=single_release,
	.read=seq_read,
	.llseek=seq_lseek,
	};
static int __init my_init(void)
{
	int value;
	int i;
	struct proc_dir_entry *file;
	//1.初始化私有结构体
	//2.初始化LED的寄存器，默认关闭
	vir_base = ioremap(GPIO_BASE, GPIO_SIZE);
	if (!vir_base) {
		printk("Cannot ioremap 0x%x(0x%x)\n", GPIO_BASE, GPIO_SIZE);
		return -EIO;
	}

	for(i=0;i<LED_NUM;i++)
	{
		leds[i].led_num=i;
		leds[i].led_state=1;
		value = readl(vir_base + GPM4CON);
		value &= ~(0xF << leds[i].led_num*4);
		value |= (0x1 << leds[i].led_num*4);
		writel(value, (vir_base + GPM4CON));

		value = readl(vir_base + GPM4DAT);
		value |= (0x1 << leds[i].led_num);
		writel(value, (vir_base + GPM4DAT));

		//注册cdev
		leds[i].dev_id = MKDEV(LED_MAJOR, leds[i].led_num);
		cdev_init(&leds[i].led_cdev, &led_fops);
		cdev_add(&leds[i].led_cdev, leds[i].dev_id, 1);
	}
	//创建proc文件
	file=proc_create("led_state", 0444, NULL, &proc_fops);	

	printk("LED char driver register OK\n");
	return 0;
}

static void __exit my_exit(void)
{
	int i;
	int value;
	remove_proc_entry("led_state", NULL);
	for(i=0;i<LED_NUM;i++)
	{
		cdev_del(&leds[i].led_cdev);
		value = readl(vir_base + GPM4DAT);
		value |= (0x1 << leds[i].led_num);
		writel(value, (vir_base + GPM4DAT));

	}
	iounmap(vir_base);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");


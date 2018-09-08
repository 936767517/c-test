#include<linux/ioport.h>
#include<linux/io.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/proc_fs.h>

#define GPIO_BASE 0x11000000
#define GPIO_SIZE 0x1000
#define GPM4CON  0x2E0
#define GPM4DAT  0x2E4

#define LED_MAJOR  60
#define LED_NUM    4
#define DEF_LED   2//控制2号灯

//定义私有结构体
struct led_priv{
	int led_num;//灯的编号0～3
	int led_state;
	dev_t dev_id;
	struct cdev led_cdev;
};

static struct led_priv led;
static int num=DEF_LED;
module_param(num,int,0444);

static void __iomem *vir_base;

static int led_proc_read (char *page,char **start,off_t off,int count,int *eof,void *data)
{
	int ret=0;
	ret=sprintf(page,"=====LED %d(%d:%d)======\n",led.led_num,MAJOR(led.dev_id),MINOR(led.dev_id));
	ret+=sprintf(page+ret,"Now:%s\n",led.led_state?"off":"on");
	return ret;
}
static int led_open(struct inode* inode,struct file *filp)
{
	return 0;
}
static int led_release(struct inode* inode,struct file *filp)
{
	return 0;	
}
static ssize_t led_write(struct file *filp,const char __user *buf,size_t count,loff_t *f_pos)
{
	int value;
	char tmp[10] = {0};
	if(copy_from_user(tmp,buf,4)){
		return -EFAULT;
	}
	if(strncmp(tmp,"on",2)==0){
		value =readl(vir_base+GPM4DAT);
		value &= ~(1<<led.led_num);
		writel(value,(vir_base+GPM4DAT));
		led.led_state=0;
	}
	else if(strncmp(tmp,"off",3)==0){
		value =readl(vir_base+GPM4DAT);
		value |= (1<<led.led_num);
		writel(value,(vir_base+GPM4DAT));
		led.led_state=1;
	}
	else {
		printk("ONLY support on off\n");
		return -1;
	}

	return count;
}
static struct file_operations led_fops ={
	.owner=THIS_MODULE,
	.open=led_open,
	.release=led_release,
	.write=led_write,
};
static int __init my_init(void)
{
	int value;
	if(num<LED_NUM){
		led.led_num=num;
	}
	else{ 
		led.led_num=DEF_LED;
	}
	led.led_state =1;
	
	vir_base=ioremap(GPIO_BASE,GPIO_SIZE);
	if(!vir_base){
		printk("cannot ioremap 0x%x(0x%x)\n",GPIO_BASE,GPIO_SIZE);
		return -EIO;
	}

	value = readl(vir_base+GPM4CON);
	value &= ~(0xf<<led.led_num*4);
	value |= (0x1<<led.led_num*4);
	writel(value,(vir_base+GPM4CON));
	
	value=readl(vir_base + GPM4DAT);
	value |= (0x1<<led.led_num);
	writel(value,(vir_base+GPM4DAT));

	led.dev_id=MKDEV(LED_MAJOR,led.led_num);
	cdev_init(&led.led_cdev,&led_fops);
	cdev_add(&led.led_cdev,led.dev_id,1);

	create_proc_read_entry("led_state",0444,NULL,led_proc_read,NULL);
	printk("LED char drive register ok\n");
	return 0;
}
static void  __exit my_exit(void)
{
	int value;
	value=readl(vir_base + GPM4DAT);
	value |= (0x1<<led.led_num);
	writel(value,(vir_base+GPM4DAT));

	remove_proc_entry("led_state",NULL);

	cdev_del(&led.led_cdev);

	iounmap(vir_base);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

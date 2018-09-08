/*****************************
 * 完整的看门狗char驱动
 * 1.提供file_operations
 * -->可以用write控制狗(echo on|off|feed)
 * -->可以用ioctl控制狗(使能，关闭，喂狗，改变喂狗的间隔，改变狗的行为等)
 * 2.提供proc文件
 * -->获得狗的当前状态
 * 3.提供中断处理函数
 * -->一旦定时器计数减为0，WDT硬件可以引起中断或RESET，为中断提供处理函数
 * -->一旦中断发生，说明长期没有喂狗，此时应该提醒用户，可以通过printk提醒，也可以利用led灯或蜂鸣器提醒
 * 4.利用锁来确保同一时间只有一个人访问WDT的寄存器
 * 5.用ioremap/readl/writel访问寄存器
 * 6.用clk_get/clk_enable来获得并使能时钟
 * 7.用platform_driver来封装
 * Author: zht
 * Date: 2015-09-09
 *******************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h> 
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include<linux/pwm.h>
#include<linux/gpio.h>
#include<mach/gpio.h>
#include<plat/gpio-cfg.h>
#include<linux/timer.h>
#include<linux/sched.h>
#include "regs-wdt.h"

//常量定义
#define MODE_IRQ	1
#define	MODE_RESET	2
#define DEF_TIME	10 //喂狗间隔默认10秒
#define DEF_MODE	MODE_IRQ
#define DEVICE_NAME  "buzz"
#define PWM_ID 0
#define PWM_GPIO EXYNOS4_GPD0(0)
//定义ioctl号
//WDT_TIME命令的参数为新的间隔秒数
//WDT_MODE命令的参数为新的模式(MODE_IRQ&MODE_RESET)
#define WDT_TYPE	'W'
#define WDT_ON		_IO(WDT_TYPE, 1)
#define WDT_OFF		_IO(WDT_TYPE, 2)
#define WDT_FEED	_IO(WDT_TYPE, 3)
#define WDT_TIME	_IOW(WDT_TYPE, 4, int)
#define WDT_MODE	_IOW(WDT_TYPE, 5, int)
#define PCLK        (100000000UL)
//由于驱动只支持一个设备，因此可以不用设计私有结构体，用全局变量保存信息
static int wdt_base; //物理地址和范围
static int wdt_size;
static struct resource *wdt_res; //request_mem_region
static void __iomem *vir_base;
static int wdt_mode;
static int wdt_time;
static int wdt_cnt; //和喂狗间隔对应的计数
static spinlock_t wdt_lock; 
static struct clk *wdt_clk;
static int  wdt_irq;
static struct pwm_device *buzzer;
 static struct timer_list pwmtimer;
 static int interval;
//proc文件的读函数
static int
wdt_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	//向用户态返回全局变量信息
	int ret=0;
	unsigned long  value;
	ret+=sprintf(page+ret,"MODE is %d\n",wdt_mode);
	ret+=sprintf(page+ret,"TIME is %d\n",wdt_time);
	ret+=sprintf(page+ret,"CNT is %d\n",wdt_cnt);

	//读WDT寄存器，向用户态返回寄存器的当前值
	value = readl(vir_base+WTCON);
	ret+=sprintf(page+ret,"WTCON is 0x%ld\n",value);
	value = readl(vir_base+WTCNT);
	ret+=sprintf(page+ret,"WTCNT is 0x%ld\n",value);
	value = readl(vir_base+WTDAT);
	ret+=sprintf(page+ret,"WTDAT is 0x%ld\n",value);
	value = readl(vir_base+WTCLRINT);
	ret+=sprintf(page+ret,"WTCLRINT is 0x%ld\n",value);
	return ret;
}

//中断处理函数
static irqreturn_t 
wdt_service(int irq, void *dev_id)
{
	//一旦计数寄存器减为0，则调用处理函数
	//可以用printk,led,buzzer等提醒用户
	printk("time is over\n");
	mod_timer(&pwmtimer,jiffies+interval);
	s3c_gpio_cfgpin(PWM_GPIO,S3C_GPIO_SFN(2));
	pwm_config(buzzer,5*100000,100000);
	pwm_enable(buzzer);
	//写WTCLRINT寄存器，清除中断状态
	writel(0,vir_base+WTCLRINT);
	return IRQ_HANDLED;
}
static void
timer_func(unsigned long data)
{
	s3c_gpio_cfgpin(PWM_GPIO,S3C_GPIO_OUTPUT);
	gpio_set_value(PWM_GPIO,0);
	pwm_disable(buzzer);
}
//file_operations
//由于write和ioctl中都支持on/off/feed等行为，可以实现若干函数来完成对应功能
void wdt_on(void)
{
	unsigned long  value;
	value=readl(vir_base+WTCON);
	value |= (WTCON_ENABLE);
	writel(value,vir_base+WTCON);
}
void wdt_off(void)
{
	unsigned long value;
	value=readl(vir_base+WTCON);
	value &= ~(WTCON_ENABLE);
	writel(value,vir_base+WTCON);
}
void wdt_feed(void)
{
	writel(wdt_cnt,vir_base+WTCNT);
}
int wdt_chg_time(unsigned long arg)
{
	unsigned long value;
	value = arg * wdt_cnt;
	writel(value,vir_base+WTCNT);
	return 0;
}
int wdt_chg_mode(unsigned long arg)
{
	unsigned long value;
	switch(arg)
	{
		case MODE_IRQ:
			value = readl(vir_base+WTCON);
			value &= ~(WTCON_RSTEN);//bit0=0
			value |= WTCON_INTEN;//bit2=1
			break;
		case MODE_RESET:
			value = readl(vir_base + WTCON);
			value &= ~(WTCON_INTEN);
			value |= WTCON_RSTEN;
			break;
		default:
			printk("only support IRQ|RESET\n");
			return -1;
	}
	return 0;
}
static ssize_t
wdt_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	//支持用户态用echo on|off|feed控制狗
	char tmp[10]={};
	unsigned long flags;
	//copy_from_user
	if(copy_from_user(tmp,buf,4))
		return -EFAULT;
	//strncmp
	//在访问寄存器之前加锁
	//访问狗的相关寄存器
	//解锁
	spin_lock_irqsave(&wdt_lock,flags);
	if(strncmp(tmp,"on",2)==0){
		wdt_on();
	}
	else if(strncmp(tmp,"off",3)==0){
		wdt_off();
	}
	else if(strncmp(tmp,"feed",4)==0){
		wdt_feed();
	}
	else{
		printk("only support on|off|feed\n");
		spin_unlock_irqrestore(&wdt_lock,flags);
		return -1;
	}
		spin_unlock_irqrestore(&wdt_lock,flags);
	return count;
}

//支持WDT_ON等命令
static long
wdt_ioctl(struct file *filp, unsigned int req, unsigned long arg)
{
	int ret;
	unsigned long flags;
	//加锁
	spin_lock_irqsave(&wdt_lock,flags);
	switch (req) {
	case WDT_ON:
		wdt_on();
		break;
	case WDT_OFF:
		wdt_off();
		break;
	case WDT_FEED:
		wdt_feed();
		break;
	case WDT_TIME:
		if(arg>21){
			printk("watchdog cannot wait so long time\n");
			spin_unlock_irqrestore(&wdt_lock,flags);
			return -1;
		}
		ret = wdt_chg_time(arg);
		break;
	case WDT_MODE:
		ret = wdt_chg_mode(arg);
		break;
	default:
		printk("cannot support this ctl\n");
		spin_unlock_irqrestore(&wdt_lock,flags);
		return -1;
	}
	//解锁
	spin_unlock_irqrestore(&wdt_lock,flags);
	return 0;
}

static struct file_operations wdt_fops = {
	.owner = THIS_MODULE,
	.write = wdt_write,
	.unlocked_ioctl = wdt_ioctl,
};

static struct miscdevice wdt_misc = {
	.minor = MISC_DYNAMIC_MINOR, 
	.name = "wdt4412",
	.fops = &wdt_fops,
};

//准备platform_driver

static int
wdt_probe(struct platform_device *pdev)
{
	int ret;
	unsigned long  flags;
	struct resource *res1, *res2;
	unsigned long value;
	struct  proc_dir_entry *file;

	//1.获得资源
	res1 = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	res2 = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res1 || !res2) {
		printk("%s(%d): Cannot get enough resource\n", pdev->name, pdev->id);
		return -1;
	}
	//初始化spinlock
	spin_lock_init(&wdt_lock);
	//2.登记寄存器，并ioremap
	wdt_base = res1->start;
	wdt_size = res1->end - res1->start + 1;
	wdt_res = request_mem_region(wdt_base, wdt_size, "mywdt");
	if (!wdt_res) {
		printk("%s(%d): request mem from 0x%x to 0x%x error\n", pdev->name, pdev->id, res1->start, res1->end);
		return -1;
	}
	else{
		printk("request mem successed\n");	
	}
	vir_base = ioremap(wdt_base, wdt_size);
	if (!vir_base) {
		ret = -EIO;
		goto err_map;
	}

	//3.获得并使能时钟，如果没有使能时钟，则不能访问WDT寄存器
	//clk结构体由三星准备，在clk_get函数中利用名字匹配，找到对应的结构体
	//三星将clk结构体集中在arch/arm/mach-exynos/clock-exynos4.c中
	wdt_clk = clk_get(&pdev->dev, "watchdog");
	if (IS_ERR(wdt_clk)) {
		ret = PTR_ERR(wdt_clk);
		goto err_clk;
	}
	clk_enable(wdt_clk);

	//4.注册中断处理函数
	wdt_irq = res2->start;
	ret=request_irq(wdt_irq,wdt_service,0,"mywdt",NULL);
	if(ret){
		printk("cannot request irq\n");
		goto err_irq;
	}
	printk("irq request successed\n");
	//5.创建proc文件
	file=create_proc_entry("wdt_test",0444,NULL);
	if(!file){
		printk("cannot create /proc/wdt_test\n");
		goto err_proc;
	}
	else{
		printk(" create /proc/wdt_test successed\n");			
	}
	file->read_proc = wdt_proc_read;
	//create_proc_read_entry("wdt_test",0444,NULL,wdt_proc_read,NULL);
	//6.初始化全局变量
	wdt_mode = DEF_MODE;
	wdt_time = DEF_TIME;
	//7.根据全局变量值，初始化WDT寄存器
	spin_lock_irqsave(&wdt_lock,flags);
	value = readl(vir_base+WTCON);
	printk("=======\n");
	value &= ~(WTCON_RSTEN);//bit0=0
	value |= WTCON_INTEN;//bit2=1

	value &=~(WTCON_DIVMASK);
	value |= WTCON_DIV128;

	value &= ~(WTCON_PRESCMASK);
	value |= WTCON_PRESC(66);

	writel(value,vir_base+WTCON);

	wdt_cnt = PCLK/128/66;
	value = wdt_cnt*wdt_time;

	writel(value,vir_base+WTDAT);
	writel(value,vir_base+WTCNT);
	spin_unlock_irqrestore(&wdt_lock,flags);
	//8.注册misc设备
	ret=misc_register(&wdt_misc);
	if(ret){
		printk("%s :register error\n",wdt_misc.name);
		goto err_misc;
	}
	else{
		printk("%s :register successed\n",wdt_misc.name);	
	}
	//9.输出成功信息printk(...);
	//申请pwm 相关
	ret=gpio_request(PWM_GPIO,DEVICE_NAME);
	if(ret){
		printk("request gpio for buzz error\n");
		goto err_gpio;
	}
	s3c_gpio_cfgpin(PWM_GPIO,S3C_GPIO_OUTPUT);
	gpio_set_value(PWM_GPIO,0);
	
	buzzer = pwm_request(PWM_ID,DEVICE_NAME);
	if(IS_ERR(buzzer)){
		printk("request pwm error\n");
		ret=PTR_ERR(buzzer);
		goto err_pwm;
	}
	//
	interval = 200*1;
	setup_timer(&pwmtimer,timer_func,0); 

	return 0;
err_pwm:
	gpio_free(PWM_GPIO);
err_gpio:
	misc_deregister(&wdt_misc);
err_misc:
	remove_proc_entry("wdt_test",NULL);
err_proc:
	free_irq(wdt_irq,NULL);
err_irq:
	clk_disable(wdt_clk);
	clk_put(wdt_clk);
err_clk:
	iounmap(vir_base);
err_map:
	release_mem_region(wdt_base,wdt_size);
	return ret;
}

static int
wdt_remove(struct platform_device *pdev)
{
	pwm_free(buzzer);
	gpio_free(PWM_GPIO);
	del_timer(&pwmtimer);
	misc_deregister(&wdt_misc);
	free_irq(wdt_irq,NULL);
	remove_proc_entry("wdt_test",NULL);
	clk_disable(wdt_clk);
	clk_put(wdt_clk);
	iounmap(vir_base);
	release_mem_region(wdt_base,wdt_size);
	return 0;
}

static struct platform_device_id my_ids[] = {
	{ "up4412-wdt", 0},
	{ "up6410-wdt", 0},
	{},
};

static struct platform_driver wdt_pdrv = {
	.probe = wdt_probe,
	.remove = wdt_remove,
	.id_table = my_ids,
	.driver = {
		.name = "mywdt-drv",
	},
};

static int __init my_init(void)
{
	printk("===========================================================\n");
	printk("drv module  has install\n");
	return platform_driver_register(&wdt_pdrv);
}

static void __exit my_exit(void)
{
	platform_driver_unregister(&wdt_pdrv);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

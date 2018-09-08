/******************************
 * 准备并注册platform_device
 * 本例针对看门狗硬件
 * Author: zht
 * Date: 2015-09-07
 ******************************/
#include <linux/module.h>
#include <linux/platform_device.h>
#include <mach/irqs.h> //中断号

//定义硬件信息
#define DEV_BASE	0x10060000
#define DEV_SIZE	0x10
#define DEV_IRQ		IRQ_WDT

//准备资源数组，resource定义在ioport.h中
static struct resource wdt_res[] = {
	[0] = {
		.start = DEV_BASE,
		.end = DEV_BASE + DEV_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DEV_IRQ,
		.end = DEV_IRQ,
		.flags = IORESOURCE_IRQ,
	},
};

//准备release函数
//如果platform_device支持注销，则需要提供release函数
//参数是platform_device中device结构体的指针
static void 
wdt_release(struct device *tmp)
{
	struct platform_device *pdev = container_of(tmp, struct platform_device, dev);
	printk("%s(%d) --> release()\n", pdev->name, pdev->id);
}


//准备platform_device
static struct platform_device wdt_pdev = {
	.name = "up4412-wdt",
	.id = -1,
	.num_resources = ARRAY_SIZE(wdt_res),
	.resource = wdt_res,
	.dev = {
		.release = wdt_release,
	},
};
	
static int __init my_init(void)
{
	//注册platform_device
	return platform_device_register(&wdt_pdev);
}

static void __exit my_exit(void)
{
	//注销platform_device
	platform_device_unregister(&wdt_pdev);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");


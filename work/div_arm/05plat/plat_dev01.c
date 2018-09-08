#include<linux/module.h>
#include<linux/platform_device.h>
#include<mach/irqs.h>

#define DEV_BASE  0x10060000
#define DEV_SIZE  0x10
#define DEV_IRQ   IRQ_WDT

static struct resource wdt_res[]={
	[0] = {
		.start = DEV_BASE,
		.end = DEV_BASE + DEV_SIZE -1,
		.flags = IORESOURCE_MEM,
	},	
	[1] = {
		.start = DEV_IRQ,
		.end = DEV_IRQ,
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device wdt_pdev={
	.name = "我家的狗",	
	.id = -1,
	.num_resource = ARRAY_SIZE(wdt_res),
	.resource = wdt_res,
};

static int __init my_init(void)
{
	return platform_device_register(&wdt_pdev);	
}
static void __exit my_exit(void)
{
	platform_device_unregister(&wdt_pdev);	
}
MODULE_INIT(my_init);
MODULE_EXIT();
MODULE_AUTHOR("HB");
MODULE_AUTHOR

#include<linux/module.h>
static int __init my_init(void)
{
	printk("Hello,kernel\n");
	return 0;
}
static void __exit my_exit(void)
{
	printk("bye,kernel\n");
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("HB");


#include<linux/module.h>

extern int value_w;
extern void my_wprint(void)
{
	printk("In 03,value=%d\n",value_w);	
}
static int __init my_init(void)
{
	printk("call 02\n");
	my_wprint();
	value_w=37;
	my_wprint();
	return 0;	
}
static void __exit my_exit(void)
{
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

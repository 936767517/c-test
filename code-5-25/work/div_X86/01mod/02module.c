#include<linux/module.h>

int value_w=10;
EXPORT_SYMBOL(value_w);
void my_wprint(void)
{
	printk("In 02,value=%d\n",value_w);	
}
EXPORT_SYMBOL(my_wprint);
static int __init my_init(void)
{
	return 0;	
}
static void __exit my_exit(void)
{
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

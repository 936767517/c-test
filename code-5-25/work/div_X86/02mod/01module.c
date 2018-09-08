#include<linux/module.h>
static int value=10;
static char* name="sherk";
module_param(value,int,0644);
module_param(name,charp,0644);
static int __init my_init(void)
{
	printk("value = %d;\n",value);
	printk("name is %s;\n",name);
	if(value==10)
		printk("ok!\n");
	else
		printk("changed!\n");
	return 0;
}
static void __exit my_exit(void)
{
	
	printk("(exit)name is %s;\n",name);
	printk("(exit)value = %d;\n",value);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

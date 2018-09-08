#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/sched.h>//jiffies
static int my_proc_read(char *page,char **start,off_t off,int count,int *eof,void *data)
{
	int ret = 0;
	ret = sprintf(page,"===proc read===\n");
	ret += sprintf(page+ret,"cureent kernel time is %ld\n",jiffies);
	return ret;
}
static int __init my_init(void)
{
	//创建proc文件
//谁申请谁释放
	struct proc_dir_entry *file;
	file=create_proc_entry("abc_ro",0444,NULL);
	if(!file){
			printk("Cannot create\n");
			return -1;
		}
		file->read_proc=my_proc_read;
	return 0;
}
static void __exit my_exit(void)
{
	//删除proc文件
	remove_proc_entry("abc_ro",NULL);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

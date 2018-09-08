#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/sched.h>//jiffies
#include<linux/uaccess.h>//copy_from_user copy_to_user
static char *str =NULL;
static int my_proc_write(struct file* filp,const char __user *buf,unsigned long count,void *data)
{
	char *tmp = kzalloc(count,GFP_KERNEL);
	if(!tmp){
			return -ENOMEM;
	}
	if(copy_from_user(tmp,buf,count)){
		kfree(tmp);
		return -EFAULT;
		}
	kfree(str);
	str=tmp;
	return count;
}
static int my_proc_read(char *page,char **start,off_t off,int count,int *eof,void *data)
{
	int ret = 0;
	ret = sprintf(page,"===proc write===\n");
	ret += sprintf(page+ret,"cureent kernel time is %ld\n",jiffies);
	ret+=sprintf(page+ret,"str is %s",str);
	return ret;
}
static int __init my_init(void)
{
	//创建proc文件
//谁申请谁释放
	struct proc_dir_entry *file;
	file=create_proc_entry("abc_rw",0644,NULL);
	if(!file){
			printk("Cannot create\n");
			return -1;
		}
		file->read_proc=my_proc_read;
		file->write_proc=my_proc_write;
	return 0;
}
static void __exit my_exit(void)
{
	//删除proc文件
	remove_proc_entry("abc_rw",NULL);
	kfree(str);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

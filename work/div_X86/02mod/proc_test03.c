#include<linux/module.h>
#include<linux/uaccess.h>
#include<linux/list.h>
#include<linux/proc_fs.h>
struct proc_head{
		struct list_head head;
		int file_size;
	};
struct proc_item{
		struct list_head item;
		char *str;
	};
static struct proc_head mylist;
//proc写函数
static int my_proc_write(struct file* filp,const char __user*buf,unsigned long count, void *data)
{
	//为proc_item申请空间
	struct 	proc_item *tmp =kzalloc(sizeof(*tmp),GFP_KERNEL);
	if(!tmp)
		return -ENOMEM;
	tmp->str =(char *)kzalloc(count+1,GFP_KERNEL);
	if(!tmp->str){
			kfree(tmp);
			return -ENOMEM;
		}
	INIT_LIST_HEAD(&tmp->item);
	if(copy_from_user(tmp->str,buf,count)){
			kfree(tmp->str);
			kfree(tmp);
			return -1;
		}
	list_add_tail(&tmp->item,&mylist.head);
	mylist.file_size+=count;
	return count;
}
static int my_proc_read(char *page,char **start,off_t off,int count,int *eof,void *data)
{
	int ret=0;
	struct proc_item *tmp;
	list_for_each_entry(tmp,&mylist.head,item){
			ret+=sprintf(page+ret,tmp->str);
		}
		ret+=sprintf(page+ret,"size = %d\n",mylist.file_size);
		return ret;
}
static int __init my_init(void)
{
	struct proc_dir_entry *file;
	INIT_LIST_HEAD(&mylist.head);
	mylist.file_size=0;
	file = create_proc_entry("abc_list",0644,NULL);
	if(!file){
		printk("cannot create /proc/abc_list\n");
		return -1;
		}
	file->read_proc=my_proc_read;
	file->write_proc=my_proc_write;
	return 0;
}
static void __exit my_exit(void)
{
	struct proc_item *tmp;
	struct proc_item *n;
	remove_proc_entry("abc_list",NULL);
	list_for_each_entry_safe(tmp,n,&mylist.head,item){
			list_del(&tmp->item);
			kfree(tmp->str);
			kfree(tmp);
		}
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("HB");
MODULE_LICENSE("GPL");

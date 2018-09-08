#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include<linux/proc_fs.h>

//主设备号  缓冲区的大小
#define MEM_MAJOR  50
#define MEM_LEN    100

//#define MEM_RESET 100
//#define MEM_RESIZE 101
#define MEM_TYPE  'M'
#define MEM_RESET _IO(MEM_TYPE,1)
#define MEM_RESIZE  _IOW(MEM_TYPE,2,int)

struct mem_priv{
	char *start;
	int buf_size;
	int wp;
	dev_t dev_id;
	struct cdev mem_cdev;
};

static struct mem_priv dev;

static int mem_open(struct inode *inode,struct file* filp)
{
	return 0;	
}
static int mem_release(struct inode *inode,struct file* filp)
{
	return 0;
}
static ssize_t mem_read(struct file *filp,char __user *buf,size_t count, loff_t *f_pos)
{
	size_t cnt=min(count,(size_t)(dev.wp-*f_pos));
	if(0==cnt)
		return 0;
	if(copy_to_user(buf,(dev.start+*f_pos),cnt))
		return -EFAULT;
	*f_pos+=cnt;
	return cnt;
}
static ssize_t mem_write(struct file *filp,const char __user *buf,size_t count,loff_t *f_pos)
{
	size_t cnt =min(count,(size_t)(dev.buf_size-dev.wp));
	if(0==cnt)
		return 0;
	if(copy_from_user(dev.start+dev.wp,buf,cnt))
		return -EFAULT;
	dev.wp+=cnt;
	return cnt;
}
static long mem_ioctl(struct file *filp,unsigned int req,unsigned long arg)
{
	char *tmp;
	switch(req){
		case MEM_RESET:
			memset(dev.start,0,dev.buf_size);
			dev.wp=0;
			break;
		case MEM_RESIZE:
			tmp=(char *)kzalloc(arg,GFP_KERNEL);
			if(!tmp)
				return -ENOMEM;
			kfree(dev.start);
			dev.buf_size=arg;
			dev.wp=0;
			dev.start=tmp;
			break;
		default:
			printk("cannot support ioctl 0x%x\n",req);
			return -1;
	}
	return 0;
}
static struct file_operations mem_fops={
	.owner=THIS_MODULE,
	.open = mem_open,
	.release = mem_release,
	.read=mem_read,
	.write=mem_write,
	.unlocked_ioctl=mem_ioctl,
	};
static int __init my_init(void)
{
	dev.buf_size=MEM_LEN;
	dev.wp=0;	
	dev.start=(char*)kzalloc(dev.buf_size,GFP_KERNEL);
	if(!dev.start)
		return -ENOMEM;
	dev.dev_id=MKDEV(MEM_MAJOR,0);
	cdev_init(&dev.mem_cdev,&mem_fops);
	cdev_add(&dev.mem_cdev,dev.dev_id,1);
	return 0;
}
static void __exit my_exit(void)
{
	cdev_del(&dev.mem_cdev);
	kfree(dev.start);
		
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

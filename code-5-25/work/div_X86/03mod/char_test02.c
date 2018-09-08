/***********************
 * 第二个char驱动的例子
 * 用内存缓冲区作为硬件，用echo向缓冲区写入数据，用cat来读缓冲区
 * 支持open/release/read/write/unlocked_ioctl
 * 本例子支持多个缓冲区
 * Author: zht
 * Date: 2015-08-26
 ************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h> //copy_to|from_user
#include <linux/cdev.h>
#include <linux/proc_fs.h>

//为设备选择主设备号，以及缓冲区的默认大小
//可以由内核自动分配alloc_chrdev_region
//也可以查看文件/proc/devices，找到一个其他驱动没有用到的主设备号
#define MEM_MAJOR	55
#define MEM_LEN		100
#define MEM_NUM		3 //3个缓冲区设备

//根据缓冲区的特点，可以支持不同的ioctl命令
//最好用内核定义好的宏来设计ioctl号
//#define MEM_RESET 	100
//#define MEM_RESIZE	101
#define MEM_TYPE	'M'
#define MEM_RESET	_IO(MEM_TYPE, 1)
#define MEM_RESIZE	_IOW(MEM_TYPE, 2, int)


//如果一个驱动支持多个设备，则应该为设备定义一个私有结构体，将每个设备不同的信息存入对应的私有结构体中
//私有结构体完全由驱动人员自行设计，设备越复杂，支持的功能越多则私有结构体成员越多
struct mem_priv {
	char *start; //缓冲区的起始地址
	int buf_size; //缓冲区的大小
	int wp; //缓冲区的写偏移
	dev_t dev_id; //设备号
	struct cdev mem_cdev; //用于注册
};

//声明一个私有结构体的数组
static struct mem_priv dev[MEM_NUM];

//增加proc文件的读函数，显示缓冲区的使用状态

//准备file_operations

static int 
mem_open(struct inode *inode, struct file *filp)
{
	//在open中，必须根据用户态打开的设备文件，找到对应的私有结构体
	//可以利用inode->i_rdev和inode->i_cdev来找到对应的私有结构体
	int i;
	struct mem_priv *tmp ;
	for(i=0;i<MEM_NUM;i++)
	{
		if(inode->i_rdev==dev[i].dev_id){
			tmp=dev+i;
			filp->private_data = tmp;
		}
	}
	return 0;
}

static int 
mem_release(struct inode *inode, struct file *filp)
{
	int i;
	struct mem_priv *tmp ;
	for(i=0;i<MEM_NUM;i++)
	{
		if(inode->i_rdev==dev[i].dev_id){
			tmp=dev+i;
			filp->private_data = tmp;
		}
	}
	return 0;
}

//对应用户态的read(fd,buf,10)
static ssize_t 
mem_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct mem_priv *tmp = filp->private_data;

	//首先判断缓冲区可以读走多少字节，如果没有可以读的，则返回0
	size_t cnt = min(count, (size_t)(tmp->wp-*f_pos));
	if (cnt == 0)
		return 0;
	//copy_to_user(to,from,cnt)
	if (copy_to_user(buf, (tmp->start+*f_pos), cnt))
		return -EFAULT;
	//更新读指针
	*f_pos += cnt;
	return cnt;
}

//对应用户态的write(fd,buf,10)
static ssize_t 
mem_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct mem_priv *tmp = filp->private_data;
	//首先确定可以向缓冲区写入多少字节，如果缓冲区已满，直接返回0
	size_t cnt = min(count, (size_t)(tmp->buf_size - tmp->wp));
	if (0 == cnt)
		return 0;
	//如果缓冲区可以写，则copy_from_user(to,from,cnt)
	if (copy_from_user((tmp->start+tmp->wp), buf, cnt))
		return -EFAULT;
	//更新写指针
	tmp->wp += cnt;
	return cnt;
}

//用户态调用ioctl(fd,命令号,参数)
//或者ioctl(fd,命令号)
static long 
mem_ioctl(struct file *filp, unsigned int req, unsigned long arg)
{
	struct mem_priv *pos = filp->private_data;
	char *tmp;
	switch (req) {
	case MEM_RESET:
		memset(pos->start, 0, pos->buf_size);
		pos->wp = 0;
		break;
	case MEM_RESIZE:
		tmp = (char *)kzalloc(arg, GFP_KERNEL);
		if (!tmp) 
			return -ENOMEM;
		kfree(pos->start);
		pos->buf_size = arg;
		pos->wp = 0;
		pos->start = tmp;
		break;
	default:
		printk("Cannot support ioctl 0x%x\n", req);
		return -1;
	}
	return 0;
}

//声明并初始化file_operations结构体
static struct file_operations mem_fops = {
	.owner = THIS_MODULE, //&__this_module
	.open = mem_open,
	.release = mem_release,
	.read = mem_read,
	.write = mem_write,
	.unlocked_ioctl = mem_ioctl,
};
static int my_proc_read(char *page,char **start,off_t off,int count,int *eof,void *data)
{
	int ret =0;
	int i;
	for(i=0;i<MEM_NUM;i++)
	{
		ret+=sprintf(page+ret,"0x%x size=%d\n",dev[i].dev_id,dev[i].wp);
	}
	return ret;
}
static int __init my_init(void)
{
	//如果增加proc文件，则一个即可
	//以下操作执行3次，每个缓冲区可以采用不同的初始大小
	//1.初始化私有结构体，并分配缓冲区
	int i;
	struct proc_dir_entry *file;
	file=create_proc_entry("abc_rw",0644,NULL);
	if(!file){
		printk("cannot create /proc/abc_rw\n");
		return -1;
		}
		file->read_proc=my_proc_read;
	for(i=0;i<MEM_NUM;i++)
	{
		dev[i].buf_size = MEM_LEN;
		dev[i].wp = 0;
		dev[i].start = (char *)kzalloc(dev[i].buf_size, GFP_KERNEL);
		if (!dev[i].start)
			return -ENOMEM;

		//2.为设备分配设备号
		dev[i].dev_id = MKDEV(MEM_MAJOR, i);

		//3.将设备号和file_ops封装在cdev结构体中，注册到VFS
		cdev_init(&dev[i].mem_cdev, &mem_fops);
		cdev_add(&dev[i].mem_cdev, dev[i].dev_id, 1);
	}
	return 0;
}

static void __exit my_exit(void)
{
	//remove_proc_entry();
	int i;
	remove_proc_entry("abc_rw",NULL);
	//以下执行3次
	for(i=0;i<MEM_NUM;i++)
	{
		cdev_del(&dev[i].mem_cdev);
		kfree(dev[i].start);
	}
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");


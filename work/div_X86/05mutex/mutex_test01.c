/****************************
 * FIFO(管道)的例子
 * 支持单个缓冲区，模拟管道的功能，用户态用echo & cat进行测试
 * 为了保证安全，用mutex对wp/rp/size等进行保护，确保同一时间一个人操作
 * Author: zht
 * Date: 2014-08-15
 ****************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/sched.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/wait.h> //wait_queue_head_t
#include <linux/mutex.h> //mutex
#include <asm/atomic.h> //atomic_t
#include<linux/seq_file.h>

#define DEF_LEN 	100
#define DEF_MAJOR 	75

//描述FIFO的私有结构体
struct mem_priv {
	char *start, *end;
	int buf_len;
	char *wp, *rp;
	//int size; //当前的字节数
	atomic_t open_cnt;
	dev_t dev_id;
	struct cdev mem_cdev;
	wait_queue_head_t writeq, readq;
	struct mutex mem_lock; //保护wp/rp/size等
};

static struct mem_priv *dev;

//在proc中显示缓冲区的当前使用状态
static int 
mem_proc_show(struct seq_file *m,void *v)
{
	seq_printf(m,"===mem state===\n");
	seq_printf(m,"start=%p\n",dev->start);
	seq_printf(m,"end=%p\n",dev->end);
	seq_printf(m,"wp=%p\n",dev->wp);
	seq_printf(m,"rp=%p\n",dev->rp);
	seq_printf(m,"cnt=%d\n",dev->wp - dev->rp);
	seq_printf(m,"bufsize=%d\n",dev->buf_len);
	return 0;
}

static int
mem_proc_open(struct inode *inode,struct file *file)
{
	return single_open(file,mem_proc_show,NULL);	
}

static int 
mem_open(struct inode *inode, struct file *filp)
{
	atomic_inc(&dev->open_cnt);
	return 0;
}


static int 
mem_release(struct inode *inode, struct file *filp)
{
	atomic_dec(&dev->open_cnt);
	return 0;
}


static ssize_t 
mem_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	size_t cnt;
	int ret;
	//首先获得锁
	while(1)
	{
		ret=mutex_lock_interruptible(&dev->mem_lock);
		if(ret)
			return -ERESTARTSYS;
		//计算有多少字节可以读
		if(dev->rp > dev->wp){	
			cnt = min(count, (size_t)((dev->end)-(dev->rp)));
		}
		else if(dev->rp <= dev->wp){
			cnt=min(count,(size_t)(dev->wp - dev->rp));
		}

		//如果缓冲区为空，首先释放锁，然后wait_event等待到缓冲区有数据可读
		if(cnt==0){
			mutex_unlock(&dev->mem_lock);
			if(wait_event_interruptible(dev->readq,dev->rp != dev->wp))
				return -ERESTARTSYS;
		}
		else
			break;
	}
	//wait_event&wait_event_interruptible 		
	//一旦缓冲区有数据可以读，首先将锁再抢回来

	//如果能确定当前持有锁，且缓冲区非空，则可以执行copy_to_user
	if(copy_to_user(buf,dev->rp,cnt)){
		mutex_unlock(&dev->mem_lock);
		return -EFAULT;
	}
	//更新rp指针，如果rp等于end，则回卷
	dev->rp += cnt;
	if (dev->rp == dev->end)
		dev->rp = dev->start;
	//解锁
	mutex_unlock(&dev->mem_lock);
	//如果缓冲区之前为满，则唤醒哪些因为缓冲区满而睡眠的进程
	wake_up_interruptible(&dev->writeq);
	return cnt;
}


	static ssize_t 
mem_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	int cnt;
	char *tmp;
	int ret;
	while(1)
	{
		//首先获得锁
		ret=mutex_lock_interruptible(&dev->mem_lock);
		if(ret)
			return -ERESTARTSYS;
		//计算有多少字节可以写
		//cnt = min(count, (size_t)(...));
		//如果缓冲区为满，首先释放锁，然后wait_event等待到缓冲区有空间可写
		//wait_event&wait_event_interruptible 		
		//一旦缓冲区有空间可写，首先将锁再抢回来
		if(dev->rp > dev->wp){
			cnt=min(count,(size_t)(dev->rp -1 - dev->wp));	
			printk("rpcnt====%d\n",cnt);
			if(cnt==0){
				tmp = dev->rp;
				mutex_unlock(&dev->mem_lock);
				if(wait_event_interruptible(dev->writeq,dev->rp != tmp))
					return -ERESTARTSYS;
			}
			else
				break;	
		}
		/*
		else if(dev->rp == dev->wp){
			cnt = min(count,(size_t)(DEF_LEN));
			printk("wpcnt====%d\n",cnt);
			break;
		}*/
		else if(dev->rp <= dev->wp){
			cnt=min(count,(size_t)((dev->end -1 - dev->wp)));
			printk("wpcnt====%d\n",cnt);
			if(cnt==0&&(dev->rp==dev->start)){
				tmp = dev->rp;
				printk("wptmp====%x\n",tmp);
				mutex_unlock(&dev->mem_lock);
				if(wait_event_interruptible(dev->writeq,dev->rp != tmp))
					return -ERESTARTSYS;
			}
			else
				break;	
		}
	}	
	//如果能确定当前持有锁，且缓冲区非满，则可以执行copy_from_user
	if(copy_from_user(dev->wp,buf,cnt)){	
		mutex_unlock(&dev->mem_lock);
		return -EFAULT;
	}
	//更新wp指针，如果wp等于end，则回卷
	dev->wp += cnt;
	if (dev->wp == dev->end)
		dev->wp = dev->start;
	//解锁
	mutex_unlock(&dev->mem_lock);
	//如果缓冲区之前为空，则唤醒那些因为缓冲区空而睡眠的进程
	wake_up_interruptible(&dev->readq);
	return cnt;
}


static struct file_operations mem_fops = {
	.owner = THIS_MODULE, 
	.open = mem_open,
	.release = mem_release,
	.read = mem_read,
	.write = mem_write,
};
static struct file_operations proc_fops={
	.owner=THIS_MODULE,
	.open=mem_proc_open,
	.release=single_release,
	.read=seq_read,
	.llseek=seq_lseek,
};

static int __init my_init(void)
{
	//int ret;
	struct proc_dir_entry *file;

	//分配并初始化私有结构体
	dev = (struct mem_priv *)kzalloc(sizeof(*dev), GFP_KERNEL);
	if (NULL == dev)
		return -ENOMEM;

	dev->start = (char *)kzalloc(DEF_LEN, GFP_KERNEL);
	if (NULL == dev->start) {
		kfree(dev);
		return -ENOMEM;
	}
	dev->buf_len = DEF_LEN;
	dev->end = dev->start + dev->buf_len;
	dev->wp = dev->start;
	dev->rp = dev->start;
	atomic_set(&dev->open_cnt, 0);

	/* init wait_queue_head */
	init_waitqueue_head(&dev->writeq);
	init_waitqueue_head(&dev->readq);

	//初始化锁
	mutex_init(&dev->mem_lock);

	/* init & add cdev */
	dev->dev_id = MKDEV(DEF_MAJOR, 0);
	cdev_init(&dev->mem_cdev, &mem_fops);
	dev->mem_cdev.owner = THIS_MODULE;
	cdev_add(&dev->mem_cdev, dev->dev_id, 1);

	/* create /proc/wait_test */
	file = proc_create("wait_test", 
		0644, NULL, &proc_fops);
	if(!file)
		return -ENOMEM;

	return 0;
}

static void __exit my_exit(void)
{
	remove_proc_entry("wait_test", NULL);
	cdev_del(&dev->mem_cdev);
	kfree(dev->start);
	kfree(dev);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZHANG");


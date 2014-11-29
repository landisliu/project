#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/sched.h>
#include<linux/version.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include <asm/uaccess.h>
#include<linux/slab.h>
#include<linux/kdev_t.h>
#include<linux/proc_fs.h>
#define ARRAYSIZE 5

#define DEBUGMODULE
int scull_quantum = 4000;
int scull_qset = 4;

struct scull_qset
{
	void **data;
	struct scull_qset *next;
};
struct scull_dev
{
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned long size;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
};

struct scull_dev p;

int scull_trim(struct scull_dev * dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset; /* "dev" is not-null */
	int i;
	for (dptr = dev->data; dptr; dptr = next)
	{ /* all the list items */
		if (dptr->data) {
			for (i = 0; i < qset; i++)
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;
	return 0;
}

struct scull_qset* scull_follow(struct scull_dev *dev, int item)
{
	struct scull_qset *dptr =dev->data;
	int i;
	for(i=0;i<item;i++)
	{
		dptr=dptr->next;
	}
	return dptr;
}

int dev_open(struct inode *inode,struct file *filp)
{
	struct scull_dev * sdev;
	sdev = container_of(inode->i_cdev,struct scull_dev,cdev);
	filp->private_data = sdev;
	if ( (filp->f_flags & O_ACCMODE) == O_WRONLY)
	{
		scull_trim(sdev); /* ignore errors */
	}
	return 0;
}

ssize_t scull_read(struct file *filp, char __user *buf, size_t count,loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr; /* the first listitem */
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset; /* how many bytes in the listitem
	*/
	int item, s_pos, q_pos, rest;
	ssize_t retval = 0;
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	if (*f_pos >= dev->size)
		goto out;
	if (*f_pos + count > dev->size)
		count = dev->size - *f_pos;
	/* find listitem, qset index, and offset in the quantum */
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;
	/* follow the list up to the right position (defined elsewhere)
	*/
	dptr = scull_follow(dev, item);
	if (dptr == NULL || !dptr->data || ! dptr->data[s_pos])
		goto out; /* don't fill holes */
	/* read only up to the end of this quantum */
	if (count > quantum - q_pos)
		count = quantum - q_pos;
	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count))
	{
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;
	out:
	up(&dev->sem);
	return retval;
}
ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = -ENOMEM; /* value used in "goto out" statements
	*/
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	/* find listitem, qset index and offset in the quantum */
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;
	/* follow the list up to the right position */
	dptr = scull_follow(dev, item);
	if (dptr == NULL)
		goto out;
	if (!dptr->data)
	{
		dptr->data = kmalloc(qset * sizeof(char *), GFP_KERNEL);
		if (!dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(char *));
	}
	if (!dptr->data[s_pos])
	{
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos])
			goto out;
	}
	/* write only up to the end of this quantum */
	if (count > quantum - q_pos)
		count = quantum - q_pos;
	if (copy_from_user(dptr->data[s_pos]+q_pos, buf, count))
	{
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;
	/* update the size */
	if (dev->size < *f_pos)
		dev->size = *f_pos;
	out:
	up(&dev->sem);
	return retval;
}

struct file_operations fo={
	.owner=THIS_MODULE,
	.read=scull_read,
	.write=scull_write,
	.llseek=NULL,
	.open=dev_open,
	.release=NULL	
	};
dev_t dev;

static int __init hello_init(void)
{
	alloc_chrdev_region(&dev, 0, 1, "chardev");
	cdev_init(&p.cdev,&fo);
	p.cdev.owner=THIS_MODULE;
	p.cdev.ops =&fo;
	p.quantum=scull_quantum;
	p.qset = scull_qset;
	cdev_add(&p.cdev,dev,1);
#ifdef DEBUGMODULE
	int start;
	for(start=0;start<100;start++)
	if(printk_ratelimit())
		printk(KERN_ALERT "chardev init success %d\n",start);
#endif
	return 0;
}
static void __exit hello_exit(void)
{
	unregister_chrdev_region(dev,3);
	cdev_del(&p.cdev);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("landis");
MODULE_DESCRIPTION("This is the first character driver i made.");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("Character Driver No.1");



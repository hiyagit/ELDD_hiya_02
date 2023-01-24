/* Kernel Synchronization Mechanisms for multiple devices */

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include <linux/kthread.h>
#include<linux/wait.h>
#include<linux/semaphore.h>

#define mem_size 50

dev_t dev = 0;
uint8_t *kernel_buffer;
static struct cdev q1_cdev;

/*************************** Function Prototypes **********************************/
static int __init q1_start(void);
static void __exit q1_end(void);
static int q1_open(struct inode *inode, struct file *file);
static int q1_release(struct inode *inode, struct file *file);
static ssize_t q1_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t q1_write(struct file *filp, const char *buf, size_t len, loff_t *off);

/***** File Operation structure *****/
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = q1_open,
	.read = q1_read,
	.write = q1_write,
	.release = q1_release,
};

static int q1_open(struct inode *inode, struct file *file)
{
	printk("Device file opened..!!\n");
	return 0;
}

static ssize_t q1_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	if(copy_to_user(buf, kernel_buffer, mem_size))
	{	
		printk("Data: error!!\n");
		return -1;
	}
	printk("Data read: done!!\n");
	return mem_size;
}

static ssize_t q1_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	if(copy_from_user(kernel_buffer, buf, len))
	{
		printk("Data: error!!\n");
		return -1;
	}
	printk("Data write: done!!\n");
	return len;
}

static int q1_release(struct inode *inode, struct file *file)
{
        printk("Device file closed..!!\n");
        return 0;
}

static int __init q1_start(void)
{
	/*Allocating Major number*/	
	if((alloc_chrdev_region(&dev, 0, 1, "q1_dev")) <0)
	{
               printk("Cannot allocate Major number\n");
               return -1;
	}
	printk("Major number: %d	Minor number: %d \n", MAJOR(dev), MINOR(dev));
	
	/*Creating cdev structure*/
	cdev_init(&q1_cdev, &fops);
	
	/*Adding character device to the system*/
	if((cdev_add(&q1_cdev, dev, 2))<0)
	{
		printk("Cannot add device to the file\n");
		unregister_chrdev_region(dev, 2);
		return -1;
	}

	kernel_buffer = kmalloc(mem_size , GFP_KERNEL);
            
	return 0;
}

static void __exit q1_end(void)
{	
	kfree(kernel_buffer);
	cdev_del(&q1_cdev);
	unregister_chrdev_region(dev, 2);
	printk("Device driver removed..!!\n");

}


module_init(q1_start);
module_exit(q1_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hiya Pandey");

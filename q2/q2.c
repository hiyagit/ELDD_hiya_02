/* Character driver using ioctl functionality */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/wait.h>

dev_t dev = 0;
static struct cdev q2_cdev;

/*************************** Function Prototypes **********************************/
static int __init q1_start(void);
static void __exit q1_end(void);
static int q2_open(struct inode *inode, struct file *file);
static int q2_release(struct inode *inode, struct file *file);
static ssize_t q2_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t q2_write(struct file *filp, const char *buf, size_t len, loff_t *off);
static long q2_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/***** File Operation structure *****/
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = q2_open,
	.read = q2_read,
	.write = q2_write,
	.unlocked_ioctl = q2_ioctl,
	.release = q2_release,
};

static int q2_open(struct inode *inode, struct file *file)
{
	printk("Device file opened..!!\n");
	return 0;
}

static int q2_release(struct inode *inode, struct file *file)
{
        printk("Device file closed..!!\n");
        return 0;
}

static ssize_t q2_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        printk("Read Function called..!!\n");
        return 0;
}

static ssize_t q2_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        printk("Write function called..!!\n");
        return len;
}

static long q2_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

}

static int __init q2_start(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "q2_dev")) <0)
	{
                printk("Cannot allocate Major number\n");
                return -1;
        }
        printk("Major number: %d	Minor number: %d \n", MAJOR(dev), MINOR(dev));
	
	/*Creating cdev structure*/
        cdev_init(&q2_cdev,&fops);

        /*Adding character device to the system*/
        if((cdev_add(&q2_cdev,dev,1)) < 0)
	{
		printk("Cannot add the device to the system\n");
             	unregister_chrdev_region(dev,1);
        	return -1;
        }

	return 0;
}

static void __exit q2_end(void)
{
        cdev_del(&q2_cdev);
        unregister_chrdev_region(dev, 1);
        printk("Device Driver removed..!!!\n");
}

module_init(q2_start);
module_exit(q2_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hiya Pandey");

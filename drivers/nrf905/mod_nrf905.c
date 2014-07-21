#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
//#include "nrf905.h"
 
MODULE_LICENSE("GPL");
#define MAJOR_NUM 1024   //Master deivce number
#define MINOR_NUM 0      //Sub device number

dev_t devnu = 0;   //device number
struct cdev cdev;  // delcre a char device

static int nrf905_open(struct inode *,struct file*);
//static int nrf905_flush(struct inode *,struct file*, unsigned int, unsigned long);
static int nrf905_close(struct inode *,struct file*);
static ssize_t nrf905_read(struct file *, char *, size_t, loff_t*);
static ssize_t nrf905_write(struct file *, const char *, size_t, loff_t*);

//declare a file operations for the device
struct file_operations nrf905_fops =
{
  .open=nrf905_open,
  //.flush=nrf905_flush,
  .release=nrf905_close,
  .read=nrf905_read,  // for read operation
  .write= nrf905_write, //for write operation
};

static void char_reg_setup_cdev (void)
{
   int error, devno = MKDEV (MAJOR_NUM, MINOR_NUM);
   cdev_init (&cdev, &nrf905_fops);
   cdev.owner = THIS_MODULE;
   cdev.ops = &nrf905_fops;
   error = cdev_add (&cdev, devno , 1);
   if (error)
       printk (KERN_NOTICE "Error %d adding char_reg_setup_cdev", error);

}

static int __init nrf905_init(void)
{
   char_reg_setup_cdev();
   return 0;
}
static void __exit nrf905_exit(void)
{
   return;
}

static int nrf905_open(struct inode *inode,struct file *file){
    /*
	if(wiringPiSetup()){
	    printk("Init failed.");
	}*/
    return 0;
}
static int nrf905_ioctl(struct inode *inode,struct file *file, unsigned int cmd, unsigned long arg){
    return 0;
}
static int nrf905_close(struct inode *inode,struct file *file){
    return 0;
}
static ssize_t nrf905_read(struct file *filp, char *buf, size_t len, loff_t *off){
    return 0;
}
static ssize_t nrf905_write(struct file *filp, const char *buf, size_t len, loff_t *off){
	return 0;
}

module_init(nrf905_init);
module_exit(nrf905_exit);
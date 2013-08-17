#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vincent dong");

static int hello_init(void){
 printk("Hello,LinuxModule.\n");
 return 0;
}

static int hello_exit(void){
 printk("Goodbye, LinuxModule.\n");
}

module_init(hello_init);
module_exit(hello_exit);

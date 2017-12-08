#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#define MAJOR_NUM 2
#define MINOR_NUM 4
#define DRIVER_NAME "Memory_Driver"
#define NO_OF_DEV 1

dev_t deviceNum;
int mem_open(struct inode* i,struct file* filp){
    printk(KERN_ALERT "%s: In open of file operation\n" ,DRIVER_NAME);
    return 0;
}

ssize_t mem_read(struct file* filp, char __user* uSpace, size_t s,loff_t* l){
    printk(KERN_ALERT "%s: In read of file operation\n" ,DRIVER_NAME);
    return 0;
}

ssize_t mem_write(struct file* filp, char __user* uSpace, size_t s,loff_t* l){
    printk(KERN_ALERT "%s: In write of file operation\n" ,DRIVER_NAME);
    return 0;
}

int mem_exit(struct inode* i,struct file* filp){
    printk(KERN_ALERT "%s: In exit of file operation\n" ,DRIVER_NAME);
    return 0;
}

struct file_operations mem_fops ={
    .owner = THIS_MODULE,
    .read= mem_read,
    .write =mem_write,
    .open = mem_open,
    .release = mem_exit
};

char *k = NULL;
static int hello_init(void){
    int ret=0;
    printk(KERN_ALERT "%s: Allocating 4K memory to kernel buffer\n" ,DRIVER_NAME);
    k= (char *)kmalloc(4096,GFP_KERNEL);
    memcpy(k,"This is in memory\0",50);
    deviceNum= MKDEV(MAJOR_NUM,MINOR_NUM);
    ret = register_chrdev_region(deviceNum,NO_OF_DEV,DRIVER_NAME);
    
    if(ret < 0){
        printk(KERN_ERR "Not able to allocate device number %d \n",ret);
        kfree(k);
        return ret;
    }
    printk(KERN_ALERT "%s: Major Number %d Minor Number %d\n", DRIVER_NAME, MAJOR(deviceNum),MINOR(deviceNum));

    return 0;
}

static int hello_exit(void){
    printk(KERN_ALERT "%s: Checking wether memory persist %s!\n",DRIVER_NAME,k);
    kfree(k);
    unregister_chrdev_region(deviceNum,NO_OF_DEV);
    return 0;
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
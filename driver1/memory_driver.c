#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

char *k = NULL;
static int hello_init(void){
    printk(KERN_ALERT "Allocating 4K memory to kernel buffer\n");
    k= (char *)kmalloc(4096,GFP_KERNEL);
    memcpy(k,"This is in memory\0",50);
    return 0;
}

static int hello_exit(void){
    printk(KERN_ALERT "Checkign wether memory persist %s!\n",k);
    kfree(k);
    return 0;
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
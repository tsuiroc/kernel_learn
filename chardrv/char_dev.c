#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include <asm/uaccess.h>

#define DEV_NAME "cuipeng"

static int dev_major = 0;
static int dev_minor = 0;

static int dev_nums = 1;
module_param(dev_nums, int, 0);

static struct class *cui_class;

static void cui_eth_init(struct net_device *dev);

typedef struct _cui_dev_s {
    int id;
    char name[10];
    struct cdev cdev;
}cui_dev_t;

cui_dev_t *pcui_devs;

static char *pdata = NULL;

struct net_device *eth_dev;

static int ethcui_open(struct net_device *d)
{
    printk("open ethcui\n");
}

static int ethcui_stop(struct net_device *d)
{
    printk("stop ethcui\n");
}

static const struct net_device_ops cui_eth_ops = {
    .ndo_open = ethcui_open,
    .ndo_stop = ethcui_stop,
};

static void cui_eth_init(struct net_device *dev)
{
    ether_setup( dev);
    dev->netdev_ops=&cui_eth_ops;
}

int cuipeng_open(struct inode *inode, struct file *filp)
{
    return 0;
}

int cuipeng_close(struct inode *inode, struct file *filp)
{
    return 0;
}

ssize_t cuipeng_read(struct file *filp, char __user *buff, size_t size, loff_t *offp)
{

    copy_to_user(buff, pdata, 10);

    return 0;
}

size_t cuipeng_write(struct file *filp, void *buff, size_t size, loff_t *offp)
{

    copy_from_user(pdata, buff, 10);
    printk("dump %s\n",pdata);

    return 0;
}

struct file_operations cdev_fops = {
    .owner = THIS_MODULE,
    .read  = cuipeng_read,
    .write = cuipeng_write,
    .open  = cuipeng_open,
};

static void cui_drv_setup_cdev(cui_dev_t *dev, int index)
{
    int ret, devno = MKDEV(dev_major, dev_minor);
    cdev_init(&dev->cdev, &cdev_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops   = &cdev_fops;
    
    ret = cdev_add(&dev->cdev, devno, 1);
    if(dev < 0)
    {
        printk("alloc dev error"); 
        return ;
    }

    return ;
}

static int __init cuipeng_init(void)
{
    printk("module init");
    dev_t dev;
    int ret;
    
    if(dev_major)
    {
        dev = MKDEV(dev_major, dev_minor);
        ret = register_chrdev_region( dev, dev_nums, DEV_NAME); 
    }
    else
    {
        ret = alloc_chrdev_region( &dev, 0, dev_nums, DEV_NAME); 
        dev_major = MAJOR(dev);
    }

    printk("\nmajor %d,minor %d",dev_major, dev_minor);
    if(dev < 0)
    {
        printk("alloc dev error"); 
        return ret;
    }

    pcui_devs = (cui_dev_t *)kmalloc(dev_nums * sizeof(cui_dev_t), GFP_KERNEL);
    if(!pcui_devs)
    {
        printk("alloc mem error"); 
        return ret;
    }

    pdata = (char *)kmalloc(10 * sizeof(char), GFP_KERNEL);
    if(!pdata)
    {
        printk("alloc mem error"); 
        return ret;
    }

    memset(pcui_devs, 0x00, dev_nums * sizeof(cui_dev_t));

    cui_dev_t *cui = NULL;
    int j = 0;
    for(cui = pcui_devs; j < dev_nums; j++, cui++)
    {
        cui->id = j;
        cui_drv_setup_cdev(cui, cui->id);
    }

    eth_dev = alloc_netdev( 0, "eth.cui", cui_eth_init);

    register_netdev(eth_dev);

    cui_class = class_create(THIS_MODULE, DEV_NAME);
    
    device_create(cui_class, NULL, dev, NULL, "%s", DEV_NAME);
    return 0;

}

static void __exit cuipeng_exit(void)
{
    if(!pcui_devs)
    kfree(pcui_devs );

    int devno = MKDEV(dev_major, dev_minor);

    unregister_chrdev_region( devno, dev_nums); 
    device_destroy(cui_class, devno);
    class_destroy(cui_class);

    if(eth_dev)
    {
        unregister_netdev(eth_dev);
        free_netdev(eth_dev);
    }

    printk("\nmodule exit");
    return;
}

module_init(cuipeng_init);
module_exit(cuipeng_exit);

MODULE_LICENSE("GPL");


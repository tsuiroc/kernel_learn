#include <linux/module.h>
#include <linux/kernel.h>
#include "prtk_module.h"

int my_printk(void)
{
    printk("\ncall %s(%s)!",__FILE__,__FUNCTION__);
    return 0;
}

EXPORT_SYMBOL_GPL(my_printk);
MODULE_LICENSE("GPL");


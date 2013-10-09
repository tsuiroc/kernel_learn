//为了测试内核进程编写
//cuipeng
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

#include <asm/signal.h>

struct task_struct *loop_printk_fun = NULL;

static int loop_printk(void *data)
{
    allow_signal(SIGKILL);

    char *ch = kmalloc(strlen((char *)data) + 1, GFP_KERNEL);

    memset(ch, 0x00, sizeof(ch));
    memcpy(ch, data, strlen(data));

    while(1)
    {
        if(kthread_should_stop()) break;
        printk("\n%s",ch);

        set_current_state(TASK_INTERRUPTIBLE);
                //TASK_UNINTERRUPTIBLE 不可以中断，TASK_INTERRUPTIBLE 可以
        schedule_timeout(5 * HZ);
    }

    return 0;
}

static int __init init_kthread(void)
{
    printk("\nmodule init");

    loop_printk_fun = kthread_run(loop_printk, "cuipeng", "loop_prtk");
    if(NULL == loop_printk_fun) return -1;

    return 0;
}


static void __exit exit_kthread(void)
{
    printk("\nmodule exit");
    kthread_stop(loop_printk_fun);

    return;

}

module_init(init_kthread);
module_exit(exit_kthread);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("崔氏小农");

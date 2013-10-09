#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/kernel.h>
//#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/delay.h>

#include <asm/system.h>
#include <asm/io.h>
#include <asm/irq.h>

int vnet_open(struct net_device *dev);
int vnet_stop(struct net_device *dev);
int vnet_xmit(struct sk_buff *skb, struct net_device *dev);

static struct net_device *vnet_dev = NULL;

static struct net_device_ops vnet_dev_ops=
{
    .ndo_open       = vnet_open,
    .ndo_stop       = vnet_stop,
    .ndo_start_xmit = vnet_xmit,
};

int vnet_open(struct net_device *dev)
{
netif_start_queue(dev);
return 0;

}

int vnet_stop(struct net_device *dev)
{
netif_stop_queue(dev);
return 0;

}

int loopback_pkt(struct sk_buff *skb, struct net_device *dev)
{


}

nt vnet_xmit(struct sk_buff *skb, struct net_device *dev)
{
    static int cnt = 0;
    
dev->stats.tx_packets++;
dev->stats.tx_bytes += skb->len; 

return 0;

}

static int vnet_init(void)
{
    vnet_dev = alloc_netdev(0, "vnet", ether_setup);

    vnet_dev->dev_addr[0] = 0x00;
    vnet_dev->dev_addr[1] = 0x00;
    vnet_dev->dev_addr[2] = 0x01;
    vnet_dev->dev_addr[3] = 0x01;
    vnet_dev->dev_addr[4] = 0x01;
    vnet_dev->dev_addr[5] = 0x00;

    vnet_dev->netdev_ops = &vnet_dev_ops;

    register_netdev(vnet_dev);

    return 0;
}

static void vnet_exit(void)
{
    unregister_netdev(vnet_dev);
    free_netdev(vnet_dev);
}

module_init(vnet_init);
module_exit(vnet_exit);

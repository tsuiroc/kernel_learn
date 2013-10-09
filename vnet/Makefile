KERN_DIR = /usr/src/kernels/2.6.32-279.el6.i686

obj-m += vnet.o
all:	
	make -C $(KERN_DIR) M=$(PWD) modules
clean:
	make -C $(KERN_DIR) M=$(PWD) modules clean


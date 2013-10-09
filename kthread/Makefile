KERNELDIR = /lib/modules/2.6.32-279.el6.i686/build/

PRINTK_MODULE += $(shell pwd)/../printk_module
KBUILD_EXTRA_SYMBOLS += $(PRINTK_MODULE)/Module.symvers
export KBUILD_EXTRA_SYMBOLS 

TARGET := loop_prtk
obj-m := $(TARGET).o

all:
	@make -C $(PRINTK_MODULE)
	@make -C $(KERNELDIR) M=$(shell pwd) modules
	@strip -S $(TARGET).ko

install:
	@make -C $(PRINTK_MODULE) install
	@insmod  $(TARGET).ko

clean:
	@make -C $(PRINTK_MODULE) clean 
	@make -C $(KERNELDIR) M=$(shell pwd) clean 


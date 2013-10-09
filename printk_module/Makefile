KERNELDIR = /lib/modules/2.6.32-279.el6.i686/build/

TARGET := prtk_module
obj-m := $(TARGET).o

all:
	@make -C $(KERNELDIR) M=$(shell pwd) modules
	@strip -S $(TARGET).ko

install:
	@insmod $(TARGET).ko

clean:
	@make -C $(KERNELDIR) M=$(shell pwd) clean 


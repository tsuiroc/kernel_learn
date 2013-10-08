KERNELDIR = /lib/modules/2.6.32-279.el6.i686/build/
obj-m := loop_prtk.o

all:
	@make -C $(KERNELDIR) M=$(shell pwd) modules

clean:
	@make -C $(KERNELDIR) M=$(shell pwd) clean 


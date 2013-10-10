KERN_DIR = /usr/src/kernels/2.6.32-279.el6.i686

obj-m += char_dev.o

.PHONY: all install clean help

all:	
	@make -C $(KERN_DIR) M=$(PWD) modules
	@gcc test.c -o test

install:	
	@insmod char_dev.ko

clean:
	@make -C $(KERN_DIR) M=$(PWD) modules clean
	@rm test -rf

help:
	@echo "1.make"
	@echo "2.make install"
	@echo "3.input:   run cmd ./test -i xxxx"
	@echo "4.display: run cmd ./test "


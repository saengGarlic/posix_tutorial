obj-m = gpioirq_module.o

KDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

default: clean
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	sudo rm -rf *.o *.ko *.mod.c .led.* Module.symvers modules.order gpio /dev/gpiopolling

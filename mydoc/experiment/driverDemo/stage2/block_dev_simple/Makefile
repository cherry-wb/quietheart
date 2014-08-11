ifneq ($(KERNELRELEASE),)
#obj-m := simpleblk.o
#simple-objs :=simpleblkdrv.o
obj-m := simpleblkdrv.o
else
KVERSION ?= $(shell uname -r)
all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) -Wall modules
	@#make -C $(PWD)/../arm-linux2.6.29 M=$(PWD) -Wall modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	@#make -C $(PWD)/../arm-linux2.6.29 M=$(PWD) clean
endif


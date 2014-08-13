###!!!set your kernel path here!!!
__KERNEL_PATH?= ../../../Kernel/
CC?=arm-sony-linux-gnueabi-dev-gcc
AR?=arm-sony-linux-gnueabi-dev-ar
ifneq ($(KERNELRELEASE),)
#obj-m := cpu1comm.o
#simple-objs :=cpu1comm_drv.o
obj-m := cpu1comm_drv.o
else
KVERSION ?= $(shell uname -r)
all:
	make -C ${__KERNEL_PATH} M=$(PWD) -Wall modules
	@#make -C /lib/modules/$(KVERSION)/build M=$(PWD) -Wall modules
clean:
	make -C ${__KERNEL_PATH} M=$(PWD) clean
	@#make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	@[ -f modules.order ] && rm -rf modules.order || :
endif


###!!!set your kernel path here!!!
#__KERNEL_PATH?= ../../../Kernel/
CC?=gcc
AR?=ar
COMM_DRV_DBG?=1
ifneq ($(COMM_DRV_DBG),)
EXTRA_CFLAGS+=-DCOMM_DRV_DBG=$(COMM_DRV_DBG)
endif

ifneq ($(KERNELRELEASE),)
#obj-m := comm.o
#simple-objs :=comm_drv.o
obj-m := comm_drv.o
else
KVERSION ?= $(shell uname -r)
all:
	@#make -C ${__KERNEL_PATH} M=$(PWD) -Wall modules
	@#make -C /lib/modules/$(KVERSION)/build M=$(PWD) -Wall modules
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) -Wall modules
clean:
	@#make -C ${__KERNEL_PATH} M=$(PWD) clean
	@#make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	@[ -f modules.order ] && rm -rf modules.order || :
	@[ -f Module.markers ] && rm -rf Module.markers || :
	@[ -f Module.symvers ] && rm -rf Module.symvers || :
	@[ -d .tmp_versions ] && rm -rf .tmp_versions || :
endif


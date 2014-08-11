ifneq ($(KERNELRELEASE),)
#obj-m := simpleblk.o
#simple-objs :=simpleblkdrv.o
obj-m := sfmem.o
else
KVERSION ?= $(shell uname -r)
all:
	make -C /root/buildTmp/eu11_environment/IA/C17/PFXBase_C17_Option/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel M=$(PWD) -Wall modules
	@#make -C /lib/modules/$(KVERSION)/build M=$(PWD) -Wall modules
clean:
	make -C /root/buildTmp/eu11_environment/IA/C17/PFXBase_C17_Option/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel M=$(PWD) clean
	@#make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
endif


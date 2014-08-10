ifneq ($(KERNELRELEASE),)
obj-m := mapmem.o
mapmem-objs :=mapmemdrv.o
else
all:
	make -C /usr/src/kernels/`uname -r`-i686/ M=$(PWD) modules
clean:
	make -C /usr/src/kernels/`uname -r`-i686/ M=$(PWD) clean
endif


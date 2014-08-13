obj-m += chardev.o
all:mymodule ioctl_test

mymodule:
	make -C /usr/src/linux-headers-`uname -r` SUBDIRS=$(PWD) modules

ioctl_test:ioctl.c
	gcc -o ioctl_test ioctl.c

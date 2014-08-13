obj-m += startstop.o
startstop-objs := start.o stop.o
default:
	make -C /usr/src/linux-headers-`uname -r` SUBDIRS=$(PWD) modules

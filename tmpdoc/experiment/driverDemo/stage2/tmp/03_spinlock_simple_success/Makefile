obj-m += simplespinlock.o
default:
	make -C /usr/src/kernels/2.6.18-194.17.4.el5-i686/ SUBDIRS=$(PWD) modules
	#make -C /usr/src/linux-headers-`uname -r` SUBDIRS=$(PWD) modules
clean:
	#for File in `ls -a` ; do echo ${File}; done;

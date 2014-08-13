obj-m += globalmem_multi.o
default:
	make -C /usr/src/linux-headers-`uname -r` SUBDIRS=$(PWD) modules
clean:
	#for File in `ls -a` ; do echo ${File}; done;

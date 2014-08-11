CC?=gcc
AR?=ar


all:
	cd drv && make COMM_DRV_DBG=1
	make COMM_API_DBG=1 -C lib
	make DBG_LOG_ON=1 -C app 
.PHONY:clean
clean:
	cd drv && make clean
	make -C lib clean
	make -C app clean

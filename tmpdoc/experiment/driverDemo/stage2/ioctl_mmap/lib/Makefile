CC=arm-sony-linux-gnueabi-dev-gcc
AR=arm-sony-linux-gnueabi-dev-ar
libcpucomm.a:cpucomm_api.o
	${AR} -qv $@ $^
cpucomm_api.o:cpucomm_api.c

.PHONY:clean
clean:
	rm -rf *.o *.a

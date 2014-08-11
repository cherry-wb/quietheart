CC=arm-sony-linux-gnueabi-dev-gcc
AR=arm-sony-linux-gnueabi-dev-ar
__TARGET=main
$(__TARGET):main.o
	${CC} -o $@ main.c -L../lib -lcpucomm
main.o:main.c

.PHONY:clean
clean:
	rm -rf *.o $(__TARGET)

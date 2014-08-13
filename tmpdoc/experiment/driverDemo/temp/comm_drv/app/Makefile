CC?=gcc
AR?=ar
DBG_LOG_ON?=1
ifneq ($(DBG_LOG_ON),)
CFLAGS+=-DDBG_LOG_ON=$(DBG_LOG_ON)
endif

__TARGET=main
$(__TARGET):main.o
	${CC} ${CFLAGS} -o $@ main.c -L../lib -lcomm -lpthread
main.o:main.c

.PHONY:clean
clean:
	rm -rf *.o $(__TARGET)

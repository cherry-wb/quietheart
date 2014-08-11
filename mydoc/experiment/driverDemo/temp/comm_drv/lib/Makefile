CC?=gcc
AR?=ar
COMM_API_DBG?=1
ifneq ($(COMM_API_DBG),)
CFLAGS+=-DCOMM_API_DBG=$(COMM_API_DBG)
endif

default:libcomm.a

libcomm.a:comm_api.o
	${AR} -qv $@ $^
comm_api.o:comm_api.c

.PHONY:clean
clean:
	rm -rf *.o *.a

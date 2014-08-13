#XXX Set the build tool name here!
#CC=gcc
#CC=/usr/local/scel8.0/arm-sony-linux-gnueabi/cross/bin/arm-sony-linux-gnueabi-gcc
CC=arm-sony-linux-gnueabi-gcc

#XXX Set the build switch
CFLAGS?=
#whether use the hex format length and offset
CFLAGS+=-DDEBUG_HEX=0
#whether open debug log
#CFLAGS+=-DDEBUG

#Variables
SRCS=flashup.c
OBJS=flashup.o
TARGET=flashup

#Rules
all:$(TARGET)

$(TARGET):$(OBJS)
	${CC} ${CFLAGS} $^ -o $@
$(OBJS):%.o:%.c

.PHONY:clean
clean:
	${RM} -rf ${OBJS}
	${RM} -rf ${TARGET}

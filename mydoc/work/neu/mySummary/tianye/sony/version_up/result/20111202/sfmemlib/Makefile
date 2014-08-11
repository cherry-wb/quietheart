#XXX Set the build tool name here!
CC=gcc
#CC=/usr/local/scel8.0/arm-sony-linux-gnueabi/cross/bin/arm-sony-linux-gnueabi-gcc
#CC=arm-sony-linux-gnueabi-gcc

#Variables
#SRCS=test_app.c Fr_verup_diablo.c
#HDRS=Fr_verup.h
OBJS=test_app.o Fr_verup_diablo.o
TARGET=test_app
LIB=libdiabloverup.a

#Rules
all:$(TARGET)

$(TARGET):$(OBJS)
	${CC} $^ -o $@
$(OBJS):%.o:%.c

LIB:$(OBJS)
	ar -qv $@ Fr_verup_diablo.o

.PHONY:clean
clean:
	${RM} -rf ${OBJS}
	${RM} -rf ${TARGET}

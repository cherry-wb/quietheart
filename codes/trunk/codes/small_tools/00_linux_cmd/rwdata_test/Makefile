#XXX Set the build tool name here!
CC=gcc

#Variables
SRCS=flashup.c
OBJS=flashup.o
TARGET=flashup

#Rules
all:$(TARGET)

$(TARGET):$(OBJS)
	${CC} $^ -o $@
$(OBJS):%.o:%.c

.PHONY:clean
clean:
	${RM} -rf ${OBJS}
	${RM} -rf ${TARGET}

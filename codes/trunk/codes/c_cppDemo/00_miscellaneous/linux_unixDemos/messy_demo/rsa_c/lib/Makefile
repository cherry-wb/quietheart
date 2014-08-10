CC=gcc
CFLAGS=-std=c99
objects=rsa.o

default:librsa.a

librsa.a:${objects}
	ar -rv librsa.a ${objects}

.PHONY:clean
clean:
	-rm ${objects} librsa.a

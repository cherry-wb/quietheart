CC=g++
objects=md5digest.o

default:libmd5digest.a

libmd5digest.a:${objects}
	ar -rv libmd5digest.a ${objects}

.PHONY:clean
clean:
	-rm ${objects} libmd5digest.a

all:libmapmem.a
libmapmem.a:mapmem.o
	ar -r $@ mapmem.o
mapmem.o:mapmem.c
	gcc -c mapmem.c
.PHONY:clean
clean:
	$(RM) -rf *.o lib*.a

CFLAGS+=-DMYFLAG
all:testapp
testapp:test_all liba.so liba.a libb.so libb.a \
		test_static test_statica_staticb test_statica_dynamicb test_dynamica_staticb test_dynamica_dynamicb
myliba.o:myliba.c
mylib.o:mylibb.c
test_all:main.c myliba.o mylibb.o
	gcc -o $@ $^
liba.so:myliba.o
	gcc -shared -o liba.so myliba.o
libb.so:mylibb.o
	gcc -shared -o libb.so mylibb.o
liba.a:myliba.o
	ar -r liba.a myliba.o
libb.a:mylibb.o
	ar -r libb.a mylibb.o
test_static:main.c
	gcc -o $@ $< -L./ -static -la -lb
test_statica_staticb:main.c
	gcc -o $@ $< -L./ -Wl,-Bstatic -la -lb -Wl,-Bdynamic
test_statica_dynamicb:main.c
	gcc -o $@ $< -L./ -Wl,-Bstatic -la -Wl,-Bdynamic -lb
test_dynamica_staticb:main.c
	gcc -o $@ $< -L./ -Wl,-Bdynamic -la -Wl,-Bstatic -lb -Wl,-Bdynamic
test_dynamica_dynamicb:main.c
	gcc -o $@ $< -L./ -la -lb
.PHONY:clean
clean:
	rm *.o *.a *.so test*

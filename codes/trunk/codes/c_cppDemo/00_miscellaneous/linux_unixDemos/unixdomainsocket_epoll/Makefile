all:server client1 client2
server:server.c epollfd.c unixsocket.c
	gcc -o $@ $^

client1:client1.c unixsocket.c
	gcc -o $@ $^

client2:client2.c unixsocket.c
	gcc -o $@ $^

.PHONY: clean
clean:
	rm -rf server client1 client2 ./tmp

all:server client
server:server.c common.h
	gcc -o $@ $^

client:client.c common.h
	gcc -o $@ $^

.PHONY:clean
clean:
	@rm server client

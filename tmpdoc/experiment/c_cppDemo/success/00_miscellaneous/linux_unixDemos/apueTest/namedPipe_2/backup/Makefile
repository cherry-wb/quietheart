CC = gcc
OBJS = fifo_write fifo_read
CFLAGS = -Wall -O2 -g

all: fifo_write fifo_read

fifo_write: fifo_write.c
$(CC) $(CFLAGS) $^ -o $@

fifo_read: fifo_read.c
$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean dist distclean
clean:
rm -rf $(OBJS) myfifo

dist:
tar zcvf fifo.tar.gz * && echo "OK"

distclean:
rm -rf $(OBJS) fifo.tar.gz myfifo

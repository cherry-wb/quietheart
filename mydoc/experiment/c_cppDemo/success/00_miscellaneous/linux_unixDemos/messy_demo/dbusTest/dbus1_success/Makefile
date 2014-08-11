all: rcv snd
snd:sendExample.c
	gcc -o snd sendExample.c `pkg-config --cflags --libs gtk+-2.0 dbus-glib-1`
rcv:receiveExample.c
	gcc -o rcv receiveExample.c `pkg-config --cflags --libs gtk+-2.0 dbus-glib-1`
#gcc -o program1 program1.c `pkg-config --cflags --libs gtk+-2.0 dbus-glib-1`

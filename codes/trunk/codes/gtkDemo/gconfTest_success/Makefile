all:client_listen client_change
client_listen:client_listen.c
	gcc -o client_listen client_listen.c `pkg-config --cflags --libs gtk+-2.0 gconf-2.0`
client_change:
	gcc -o client_change client_change.c `pkg-config --cflags --libs gtk+-2.0 gconf-2.0`

all:libplugin.so win
libplugin.so:plugin.c
	gcc -shared -o libplugin.so plugin.c `pkg-config --cflags --libs gtk+-2.0`
win:win.c
	gcc -o win win.c `pkg-config --cflags --libs gtk+-2.0`

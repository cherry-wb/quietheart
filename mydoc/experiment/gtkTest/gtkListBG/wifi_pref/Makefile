wifi_pref: wifi_pref.c applet.h
	gcc -g -o wifi_pref wifi_pref.c `pkg-config --cflags --libs gtk+-2.0` -L /usr/local/lib/libwifi/ -liwlist -liwconfig
#for make on pc
pc: wifi_pref2

wifi_pref2: wifi_pref.c applet.h
	gcc -DMY_PC_DEBUG=1 -g -o wifi_pref2 wifi_pref.c `pkg-config --cflags --libs gtk+-2.0`

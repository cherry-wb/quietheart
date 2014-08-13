all:server-bindings.h client-bindings.h rcv2
rcv2:server-bindings.h rcv2.c
	gcc -o rcv2 rcv2.c `pkg-config --cflags --libs gtk+-2.0 dbus-glib-1`
server-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=server_object --mode=glib-server $<> $@

client-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=server_object --mode=glib-client $<> $@

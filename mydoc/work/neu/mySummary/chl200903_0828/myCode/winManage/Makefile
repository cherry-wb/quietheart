all: list printActiveInfo printAllWinInfo getCurWinPID getCurWinID close closeActive getWinByTitle
	-echo 'make all the targets'
list:winManage.c example_list.c
	gcc -o list winManage.c example_list.c `pkg-config --cflags --libs gtk+-2.0`
printActiveInfo:winManage.c example_printActiveInfo.c
	gcc -o printActiveInfo winManage.c example_printActiveInfo.c `pkg-config --cflags --libs gtk+-2.0`
printAllWinInfo:winManage.c example_printAllWinInfo.c
	gcc -o printAllWinInfo winManage.c example_printAllWinInfo.c `pkg-config --cflags --libs gtk+-2.0`
getCurWinPID:winManage.c example_getCurWinPID.c
	gcc -o getCurWinPID winManage.c example_getCurWinPID.c `pkg-config --cflags --libs gtk+-2.0`
getCurWinID:winManage.c example_getCurWinID.c
	gcc -o getCurWinID winManage.c example_getCurWinID.c `pkg-config --cflags --libs gtk+-2.0`
close:winManage.c example_close.c
	gcc -o close winManage.c example_close.c `pkg-config --cflags --libs gtk+-2.0`
closeActive:winManage.c example_closeActive.c
	gcc -o closeActive winManage.c example_closeActive.c `pkg-config --cflags --libs gtk+-2.0`
getWinByTitle:winManage.c example_getWinByTitle.c
	gcc -o getWinByTitle winManage.c example_getWinByTitle.c `pkg-config --cflags --libs gtk+-2.0`

#include "winManage.h"
/*列出当前所有的窗口，缺点：输出警告信息，不知道原因*/
gint main(gint argc, gchar *argv[])
{
	g_print("The columns of windows are:\n");
	g_print("winID  deskNum  PID  winClass  clientMachine  winTitle\n");
	g_print("------------------------------------------------------\n");
	if(argc == 1)
	{
		setlocale(LC_ALL, "");
		init_charset();/*lkadd*/
		Display *disp;
		if (! (disp = XOpenDisplay(NULL)))
		{
			fputs("Cannot open display.\n", stderr);
			return 1;
		}/*打开显示*/
		list_windows(disp);
		g_print("------------------------------------------------------\n");
		XCloseDisplay(disp);
	}
	else
	{
		g_print("usage: %s\n", argv[0]);
	}
	return 0;
}

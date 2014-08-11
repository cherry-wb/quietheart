/*程序功能：
 * 给定窗口标题,获取具有这个窗口标题的窗口列表,
 * 打印每一个窗口的信息*/
#include "winManage.h"
gint main(gint argc, gchar *argv[])
{
	if(argc == 2)
	{
		setlocale(LC_ALL, "");
		init_charset();/*lkadd*/
		Display *disp;
		Window *win;
		int count = 0;
		int i = 0;
		if (! (disp = XOpenDisplay(NULL)))
		{
			fputs("Cannot open display.\n", stderr);
			return 1;
		}/*打开显示*/
		win = get_window_by_title(disp, argv[1], &count);
		for(i = 0; i < count; ++i)
		{
			print_win_info(disp, &win[i]);
		}
		free(win);
		XCloseDisplay(disp);
	}
	else
	{
		g_print("usage: %s windowTitle\n",argv[0]);
	}
	return 0;
}

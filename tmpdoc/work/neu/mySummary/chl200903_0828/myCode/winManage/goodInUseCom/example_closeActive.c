
#include "winManage.h"


static gchar* getActiveWinTitle(Display *disp);

gint main(gint argc, gchar *argv[])
{
	if(argc == 1)
	{
		Display *disp;
		setlocale(LC_ALL, "");
		init_charset();
		if (! (disp = XOpenDisplay(NULL)))
		{
			fputs("Cannot open display.\n", stderr);
			return ;
		}


		
		gchar* activeWinTitle = getActiveWinTitle(disp);
		close_win_by_title(activeWinTitle);

		g_free(activeWinTitle);
		XCloseDisplay(disp);
	}
	else
	{
		g_print("usage: %s \n",argv[0]);
	}
	return 0;
}
static gchar* getActiveWinTitle(Display *disp)
{
	Window win = get_active_window(disp);
#if MY_DEBUG_OUTPUT == 1
	g_print("before get_window_title**\n");
#endif
	return get_title_by_window(disp,win);
}

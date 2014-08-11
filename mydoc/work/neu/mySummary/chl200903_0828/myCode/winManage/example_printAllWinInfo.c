/*本程序功能：
获取当前所有窗口,打印窗口总数,并打印每个窗口相关信息。
 * */
#include "winManage.h"
void print_active_window_info();
gint main(gint argc, gchar *argv[])
{
	if(argc == 1)
	{
		Display *disp;
		/*存放窗口数目*/
		int count = 0;
		int i = -1;

		setlocale(LC_ALL, "");
		init_charset();
		if (! (disp = XOpenDisplay(NULL)))
		{
			fputs("Cannot open display.\n", stderr);
			return ;
		}/*打开显示*/

		Window *win = get_window_list(disp, &count);/*获得活动窗口*/
		g_print("The window count is:%d\nand they are:\n", count);
		for(i = 0; i < count; ++i)
		{
			print_win_info(disp, &win[i]);
		}
		g_free(win);
		XCloseDisplay(disp);
	}
	else
	{
		g_print("usage: %s \n",argv[0]);
	}
	return 0;
}

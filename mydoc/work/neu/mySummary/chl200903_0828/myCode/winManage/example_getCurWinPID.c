/*本程序功能：
获取当前活动窗口对应pid
 * */
#include "winManage.h"
gint main(gint argc, gchar *argv[])
{
	if(argc == 1)
	{
		Display *disp;
		if (! (disp = XOpenDisplay(NULL)))
		{
			fputs("Cannot open display.\n", stderr);
			return ;
		}/*打开显示*/


		/*获得活动窗口*/
		Window win = get_active_window(disp);
		/*获得活动窗口对应的进程id*/
		unsigned long pid = get_pid_by_window(disp, win);
		g_print("the pid of current window is %d\n", pid);
		XCloseDisplay(disp);
	}
	else
	{
		g_print("usage: %s \n",argv[0]);
	}
	return 0;
}

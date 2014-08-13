/*本程序功能：
获取当前活动窗口对应id
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
		unsigned winId = (unsigned)win;
		/*获得活动窗口对应的进程id*/
		g_print("the id of current window is %d\n", winId);
		g_print("the id of current window in hex is 0x%x\n", winId);
		XCloseDisplay(disp);
	}
	else
	{
		g_print("usage: %s \n",argv[0]);
	}
	return 0;
}

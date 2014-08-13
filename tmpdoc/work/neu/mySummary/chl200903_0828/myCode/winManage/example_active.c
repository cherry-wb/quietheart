/*功能：激活指定标题的窗口
 * */
#include "winManage.h"
int main(int argc, char *argv[])
{
	Display *disp;
	Window *win = NULL;
	gchar *title;
	if (! (disp = XOpenDisplay(NULL)))
	{
		fputs("Cannot open display.\n", stderr);
		return ;
	}/*打开显示*/
//	win = (Window*)get_active_window(disp);
//	title = get_window_title (disp, win);
//	g_print("the title of the current window is:%s\n", title);
//
//    g_free(title);
//	XCloseDisplay(disp);
	return 0;
}

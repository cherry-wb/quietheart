/*本程序功能：
获取当前活动窗口,获取并打印窗口标题，窗口类型以及对应pid
 * */
#include "winManage.h"
void print_active_window_info();
gint main(gint argc, gchar *argv[])
{
	if(argc == 1)
	{
		print_active_window_info();
	}
	else
	{
		g_print("usage: %s \n",argv[0]);
	}
	return 0;
}
/*打印当前活动窗口的信息*/
void print_active_window_info()
{
	Display *disp;
	setlocale(LC_ALL, "");
	init_charset();
	if (! (disp = XOpenDisplay(NULL)))
	{
		fputs("Cannot open display.\n", stderr);
		return ;
	}/*打开显示*/
	Window win = get_active_window(disp);/*获得活动窗口*/
#if MY_DEBUG_OUTPUT == 1
	g_print("before get_window_title**\n");
#endif
	gchar *title = get_title_by_window(disp,win);/*获得活动窗口的标题*/
	gchar *class = get_window_class(disp, win); /*获得活动窗口所属的类UTF8 */
	unsigned long pid = get_pid_by_window(disp, win);/*获得活动窗口对应的进程id*/


	g_print("the id of current window is %d\n", win);
	g_print("active window title is:%s\n", title);
	g_print("active window class is:%s\n", class);
	g_print("active window pid is:%d\n", pid);

	g_free(title);
	g_free(class);
	XCloseDisplay(disp);
}

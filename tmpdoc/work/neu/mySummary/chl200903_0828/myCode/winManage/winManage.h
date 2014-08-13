/*一些操作窗口的基本函数编写，并且附有小例子。
 *代码从wmctrl摘抄并改进过来的。没有完成的注释有*****
 * */
#ifndef __winManage_H
#define __winManage_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>
#include <glib.h>

#define MAX_PROPERTY_VALUE_LEN 4096
#ifndef MY_DEBUG_OUTPUT
#define MY_DEBUG_OUTPUT 0
#endif

/*user use{*/
/*列出所有窗口信息*/
int list_windows (Display *disp);

/*根据指定的标题关闭窗口*/
int close_win_by_title(gchar *title);

/*获得指定窗口的标题，注意返回值需要释放！！*/
gchar *get_title_by_window(Display *dpy, Window win);

/*获得当前活动窗口*/
Window get_active_window(Display *dpy);

/*获得指定窗口的类型UTF8*/
gchar *get_window_class (Display *disp, Window win);

/*根据指定的窗口获得相应的pid值*/
unsigned long get_pid_by_window(Display *disp, Window win);

/*获得当前窗口列表, 返回Window数组，存放窗口数目到参数count中*/
Window *get_window_list(Display *disp, int *count);

/*指定一个标题获得相应窗口，如果多个匹配，返回一个数组,并且数目存放到count中。
 * 注意使用完毕释放返回数组*/
Window* get_window_by_title(Display *dpy, gchar *title, int *count);

/*打印指定窗口的信息*/
void print_win_info(Display *dpy, Window *win);

/*获得指定窗口的id*/
//只需要把Window类型转换为整数类型就行了

/*根据窗口ID关闭窗口*********/
//int close_win_by_id();
/*激活指定窗口*************/
//int active_by_window(Display *dpy, Window *win);
/*根据winID激活指定窗口*/
/*user use}*/
void init_charset(void);
int activate_window (Display *disp, Window win, gboolean switch_desktop);
#endif

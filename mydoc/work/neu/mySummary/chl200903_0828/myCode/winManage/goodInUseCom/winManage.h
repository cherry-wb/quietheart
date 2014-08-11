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



int list_windows (Display *disp);

int close_win_by_title(gchar *title);


gchar *get_title_by_window(Display *dpy, Window win);


Window get_active_window(Display *dpy);

gchar *get_window_class (Display *disp, Window win);

unsigned long get_pid_by_window(Display *disp, Window win);

Window *get_window_list(Display *disp, int *count);



void init_charset(void);
int activate_window (Display *disp, Window win, gboolean switch_desktop);
#endif

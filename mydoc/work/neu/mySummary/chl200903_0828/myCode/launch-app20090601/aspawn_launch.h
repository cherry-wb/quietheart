#ifndef __ASPAWN_LAUNCH_H
#define __ASPAWN_LAUNCH_H
#include<stdio.h>
#include<gtk/gtk.h>
/*for window manipulator*/
#include <stdlib.h>
#include <X11/Xatom.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>
#include <glib.h>
#include <glib/gprintf.h>

#ifndef MY_DEBUG_OUTPUT
#define MY_DEBUG_OUTPUT 1
#endif

#define MAX_PROPERTY_VALUE_LEN 4096
static gboolean envir_utf8;
static struct {
    int verbose;
    int force_utf8;
    int show_class;
    int show_pid;
    int show_geometry;
    int match_by_id;
	int match_by_cls;
    int full_window_title_match;
    int wa_desktop_titles_invalid_utf8;
    char *param_window;
    char *param;
} options;
static Window *client_list = NULL;/*窗口列表相关*/
/*user functions*/

/*This function launch the application. If it already exist,just top it.
 *This function can be portable to other source need it. 
 *To lauch the application you should know the window title of it before. */
int launchApp_portable(char *appPath, char *appWinTitle);

/*This function launch the application. If it already exist,just top it.
 *This function calls the launchApp_portable, not portable.
 It is only used by us, because we know the window Title ourselves. */
int launchApp(char *appPath);

/*get the number of windows exist*/
int getWindowCount(void);
#endif

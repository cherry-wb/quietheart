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
int launchApp_portable(char *appPath, char *appWinTitle);
int launchApp(char *appPath);
int getWindowCount(void);
int main(int argc, char *argv[])
{
	/*this show the usage of the function*/
	if(2 != argc)
	{
		g_print("usage: %s applicationCommand\n",argv[0]);
		return 1;
	}
	else
	{
		/*launch application by command*/
		g_print("the command you input is %s .\n", argv[1]);
		launchApp(argv[1]);
		/*get the count of the window exists*/
		int count = getWindowCount();
		g_print("the count of the windows exists is %d .\n", count);
		return 0;
	}
}

/*the declaration of functions*/


/*the defination of the functions*/

/*charset*/
static void init_charset (void)
{
    const gchar *charset; /* unused */
    gchar *lang = getenv("LANG") ? g_ascii_strup(getenv("LANG"), -1) : NULL; 
    gchar *lc_ctype = getenv("LC_CTYPE") ? g_ascii_strup(getenv("LC_CTYPE"), -1) : NULL;
    
    /* this glib function doesn't work on my system ... */
    envir_utf8 = g_get_charset(&charset);

    /* ... therefore we will examine the environment variables */
    if (lc_ctype && (strstr(lc_ctype, "UTF8") || strstr(lc_ctype, "UTF-8"))) {
        envir_utf8 = TRUE;
    }
    else if (lang && (strstr(lang, "UTF8") || strstr(lang, "UTF-8"))) {
        envir_utf8 = TRUE;
    }

    g_free(lang);
    g_free(lc_ctype);
    
    if (options.force_utf8) {
        envir_utf8 = TRUE;
    }
    g_print("envir_utf8: %d\n", envir_utf8);
}


/*send msg to client???*/
static int client_msg(Display *disp, Window win, char *msg, 
        unsigned long data0, unsigned long data1, 
        unsigned long data2, unsigned long data3,
        unsigned long data4)
{
    XEvent event;
    long mask = SubstructureRedirectMask | SubstructureNotifyMask;

    event.xclient.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.message_type = XInternAtom(disp, msg, False);
    event.xclient.window = win;
    event.xclient.format = 32;
    event.xclient.data.l[0] = data0;
    event.xclient.data.l[1] = data1;
    event.xclient.data.l[2] = data2;
    event.xclient.data.l[3] = data3;
    event.xclient.data.l[4] = data4;
    
    if (XSendEvent(disp, DefaultRootWindow(disp), False, mask, &event)) {
        return EXIT_SUCCESS;
    }
    else {
        fprintf(stderr, "Cannot send %s event.\n", msg);
        return EXIT_FAILURE;
    }
}



/*get the property of the window*/
static gchar *get_property (Display *disp, Window win,Atom xa_prop_type, gchar *prop_name, unsigned long *size)
{
    Atom xa_prop_name;
    Atom xa_ret_type;
    int ret_format;
    unsigned long ret_nitems;
    unsigned long ret_bytes_after;
    unsigned long tmp_size;
    unsigned char *ret_prop;
    gchar *ret;
    
    xa_prop_name = XInternAtom(disp, prop_name, False);
    
    if (XGetWindowProperty(disp, win, xa_prop_name, 0, MAX_PROPERTY_VALUE_LEN / 4, False,
            xa_prop_type, &xa_ret_type, &ret_format,     
            &ret_nitems, &ret_bytes_after, &ret_prop) != Success) {
	g_print("Cannot get %s property.\n, prop_name");
        return NULL;
    }
  
    if (xa_ret_type != xa_prop_type) {
        g_print("Invalid type of %s property.\n", prop_name);
        XFree(ret_prop);
        return NULL;
    }

    /* null terminate the result to make string handling easier */
    tmp_size = (ret_format / 8) * ret_nitems;
    /* Correct 64 Architecture implementation of 32 bit data */
    if(ret_format==32) tmp_size *= sizeof(long)/4;
    ret = g_malloc(tmp_size + 1);
    memcpy(ret, ret_prop, tmp_size);
    ret[tmp_size] = '\0';

    if (size) {
        *size = tmp_size;
    }
    
    XFree(ret_prop);
    return ret;
}

/*get window title*/
static gchar *get_window_title (Display *disp, Window win)
{
    gchar *title_utf8;
    gchar *wm_name;
    gchar *net_wm_name;

    wm_name = get_property(disp, win, XA_STRING, "WM_NAME", NULL);
    net_wm_name = get_property(disp, win, 
            XInternAtom(disp, "UTF8_STRING", False), "_NET_WM_NAME", NULL);

    if (net_wm_name) {
        title_utf8 = g_strdup(net_wm_name);
    }
    else {
        if (wm_name) {
            title_utf8 = g_locale_to_utf8(wm_name, -1, NULL, NULL, NULL);
        }
        else {
            title_utf8 = NULL;
        }
    }

    g_free(wm_name);
    g_free(net_wm_name);
    
    return title_utf8;
}

/*get window class*/
static gchar *get_window_class (Display *disp, Window win)
{
    gchar *class_utf8;
    gchar *wm_class;
    unsigned long size;

    wm_class = get_property(disp, win, XA_STRING, "WM_CLASS", &size);
    if (wm_class) {
        gchar *p_0 = strchr(wm_class, '\0');
        if (wm_class + size - 1 > p_0) {
            *(p_0) = '.';
        }
        class_utf8 = g_locale_to_utf8(wm_class, -1, NULL, NULL, NULL);
    }
    else {
        class_utf8 = NULL;
    }

    g_free(wm_class);
    
    return class_utf8;
}


/*???*/
static gchar *get_output_str (gchar *str, gboolean is_utf8)
{
    gchar *out;
   
    if (str == NULL) {
        return NULL;
    }
    
    if (envir_utf8) {
        if (is_utf8) {
            out = g_strdup(str);
        }
        else {
            if (! (out = g_locale_to_utf8(str, -1, NULL, NULL, NULL))) {
                g_print("Cannot convert string from locale charset to UTF-8.\n");
                out = g_strdup(str);
            }
        }
    }
    else {
        if (is_utf8) {
            if (! (out = g_locale_from_utf8(str, -1, NULL, NULL, NULL))) {
                g_print("Cannot convert string from UTF-8 to locale charset.\n");
                out = g_strdup(str);
            }
        }
        else {
            out = g_strdup(str);
        }
    }

    return out;
}

/*get list of client window*/
static Window *get_client_list (Display *disp, unsigned long *size)
{
    Window *client_list;

    if ((client_list = (Window *)get_property(disp, DefaultRootWindow(disp), 
                    XA_WINDOW, "_NET_CLIENT_LIST", size)) == NULL) {
        if ((client_list = (Window *)get_property(disp, DefaultRootWindow(disp), 
                        XA_CARDINAL, "_WIN_CLIENT_LIST", size)) == NULL) {
            fputs("Cannot get client list properties. \n"
                  "(_NET_CLIENT_LIST or _WIN_CLIENT_LIST)"
                  "\n", stderr);
            return NULL;
        }
    }

    return client_list;
}

/*active window*/
static int activate_window (Display *disp, Window win, 
        gboolean switch_desktop)
{
    unsigned long *desktop;

    /* desktop ID */
    if ((desktop = (unsigned long *)get_property(disp, win,
            XA_CARDINAL, "_NET_WM_DESKTOP", NULL)) == NULL) {
        if ((desktop = (unsigned long *)get_property(disp, win,
                XA_CARDINAL, "_WIN_WORKSPACE", NULL)) == NULL) {
            g_print("Cannot find desktop ID of the window.\n");
        }
    }

    if (switch_desktop && desktop) {
        if (client_msg(disp, DefaultRootWindow(disp), 
                    "_NET_CURRENT_DESKTOP", 
                    *desktop, 0, 0, 0, 0) != EXIT_SUCCESS) {
            g_print("Cannot switch desktop.\n");
        }
        g_free(desktop);
    }

    client_msg(disp, win, "_NET_ACTIVE_WINDOW", 
            0, 0, 0, 0, 0);
    XMapRaised(disp, win);

    return EXIT_SUCCESS;
}

/*active the window called by you*/
static void active_window(Window *win)
{
	Display *disp;
	gchar *title_utf8 = NULL;
    if (! (disp = XOpenDisplay(NULL))) {
        fputs("Cannot open display.\n", stderr);
        return ;
    }

	if(NULL != win)
	{
		title_utf8 = get_window_title(disp, *win); /* UTF8 */
		g_print("*****the title of the window to activate is %s\n", title_utf8);
		activate_window (disp, *win,TRUE); 
	}
	else
	{
		g_print("*****the window you want to active is NULL!\n");
	}
    XCloseDisplay(disp);
    g_free(title_utf8);
}

/*find window by Title, 
 * if the windows exists return 1 and store the window in win,else return 0*/

static int findWindowByTitle (Display *disp, char *title, Window **win)
{
    unsigned long client_list_size;
    int i;
    if ((client_list = get_client_list(disp, &client_list_size)) == NULL)
	{
		g_print("cann't get the window list!*****\n");
        return -1; 
    }
    
    /* get title,and find by title*/
    for (i = 0; i < client_list_size / sizeof(Window); i++)
	{
        gchar *title_utf8 = get_window_title(disp, client_list[i]); /* UTF8 */
        gchar *title_out = get_output_str(title_utf8, TRUE);
        gchar *class_out = get_window_class(disp, client_list[i]); /* UTF8 */

		if(NULL != title_out)
		{
			if(strcmp(title_out, title) == 0)
			{/*find the window*/
				*win = &client_list[i];
				g_free(title_utf8);
				g_free(title_out);
				g_free(class_out);
				return 1;
			}
		}
		else
		{/*if the application don't have win title judge by class*/
			if(strcmp(class_out, title) == 0)
			{/*find the window*/
				*win = &client_list[i];
				g_free(title_utf8);
				g_free(title_out);
				g_free(class_out);
				return 1;
			}
		}

		if(strcmp(class_out, title) == 0)
		{/*if have title and have class name and don't judge by title*/
			*win = &client_list[i];
			g_free(title_utf8);
			g_free(title_out);
			g_free(class_out);
			return 1;
		}
		g_free(title_utf8);
		g_free(title_out);
		g_free(class_out);
    }
	/*can't find the window by title*/
    return 0;
}

/*This function launch the application. If it already exist,just top it.
 *This function can be portable to other source need it. 
 *To lauch the application you should know the window title of it before. */
int launchApp_portable(char *appCmd, char *appWinTitle)
{
	init_charset();/*lkadd*/
	if(appCmd != NULL)
	{/*if input is not NULL*/
		gint argc;/*parameter number*/
		gchar **argv = NULL;/*parameter*/
		GError *error = NULL;
		GPid child_pid;

		int exists = 0;/*if the application has already exists*/
		Window *win = NULL;
		Display *disp;

		if(! (disp = XOpenDisplay(NULL)))
		{
			fputs("Cannot open display.\n", stderr);
			return ;
		}
		exists = findWindowByTitle(disp, appWinTitle, &win);
		XCloseDisplay(disp);
		if(1 == exists)
		{/*if the application exists just active it*/
			active_window(win);
			if(client_list != NULL)
			{
				g_free(client_list);
				client_list = NULL;
			}
		}
		else if(0 == exists)
		{
			if(client_list != NULL)
			{
				g_free(client_list);
				client_list = NULL;
			}
			/*****launch the applications here!*****/
			if(g_shell_parse_argv (appCmd, &argc, &argv, &error))
			{
#if MY_DEBUG_OUTPUT == 1
				g_print("the application command is '%s' \n", appCmd);
				g_print("the application path is '%s'\n", argv[0]);
				g_print("the first parameter is '%s'\n", argv[1]);
				g_print("the parameter number is '%d'\n", argc);
#endif
				g_spawn_async(
						/* Child's current working directory,
						   or NULL to inherit parent's */
						NULL,
						/* Child's argument vector. [0] is the path of
						   the program to execute */
						argv,
						/* Child's environment, or NULL to inherit
						   parent's */
						NULL,
						/* Flags from GSpawnFlags */
						0,
						/* Function to run in the child just before
						   exec() */
						NULL,
						/* User data for child_setup */
						NULL,
						/* Return location for child process ID or NULL */
						&child_pid,
						/* Return location for error */
						&error);/*lkcomment异步执行子程序*/

				if (argv)
					g_strfreev (argv);
				return 0;
			}
			if (error)
			{
				g_print("failed to execute!*****\n");

				g_clear_error (&error);
			}
			g_print("spawn failed************\n");
			return 1;

		}
		else
		{
			g_print("error when find window by Title!*****\n");
			return 1;
		}
	}
	else
	{
		g_print("appCmd is NULL!!********\n");
		return 1;
	}
}


/*This function launch the application. If it already exist,just top it.
 *This function calls the launchApp_portable, not portable.
 It is only used by us, because we know the window Title ourselves. */
int launchApp(char *appCmd)
{
	gint argc;/*parameter number*/
	gchar **argv = NULL;/*parameter*/
	GError *error = NULL;
	if(g_shell_parse_argv (appCmd, &argc, &argv, &error))
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("the application command is '%s' \n", appCmd);
		g_print("the application path is '%s'\n", argv[0]);
		g_print("the first parameter is '%s'\n", argv[1]);
		g_print("the parameter number is '%d'\n", argc);
#endif
/*下面有问号的分支需要改变第2个参数为窗口标题。*/
		if(strcmp(argv[0],"/usr/bin/StartAudio") == 0)
		{/*audio*/
			launchApp_portable("/usr/bin/StartAudio", "AudioPlayer");
		}
		else if(strcmp(argv[0],"videoPath")== 0)
		{/*videoPath*/
			launchApp_portable("/usr/bin/StartVideo.sh", "VideoPlayer");
		}
		else if(strcmp(argv[0],"/usr/bin/abiword")== 0)
		{/*word*/
			launchApp_portable("/usr/bin/abiword", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/swkeyboard")== 0)
		{/*keyboard?????*/
			launchApp_portable("/usr/bin/swkeyboard", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/calc")== 0)
		{/*calculator*/
			launchApp_portable("/usr/bin/calc", "galculator");
		}
		else if(strcmp(argv[0],"/usr/bin/email")== 0)
		{/*mail?????*/
			launchApp_portable("/usr/bin/email", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/Tuxpuck")== 0)
		{/*?????*/
			launchApp_portable("/usr/bin/Tuxpuck", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/madbomber")== 0)
		{/*?????*/
			launchApp_portable("/usr/bin/madbomber", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/pidgin")== 0)
		{/*qq*/
			launchApp_portable("/usr/bin/pidgin", "Buddy List");
		}
		else if(strcmp(argv[0],"/usr/bin/excel")== 0)
		{/*/usr/bin/excel*/
			launchApp_portable("/usr/bin/excel", "Gnumeric.Gnumeric");
		}
		else if(strcmp(argv[0],"/usr/bin/IE")== 0)
		{/*/usr/bin/IE?????*/
			launchApp_portable("/usr/bin/IE", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/PowerManager")== 0)
		{/*/usr/bin/PowerManager*/
			launchApp_portable("/usr/bin/PowerManager", "Power Manager");
		}
		else if(strcmp(argv[0],"/usr/bin/epdfview")== 0)
		{/*/usr/bin/epdfview*/
			launchApp_portable("/usr/bin/epdfview", "PDF Viewer");
		}
		else if(strcmp(argv[0],"/usr/bin/record")== 0)
		{/*/usr/bin/record????????*/
			launchApp_portable("/usr/bin/record", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/note")== 0)
		{/*/usr/bin/note*/
			launchApp_portable("/usr/bin/note", "MaemoPad");
		}
		else if(strcmp(argv[0],"/usr/bin/shutdown")== 0)
		{/*/usr/bin/shutdown??????*/
			launchApp_portable("/usr/bin/shutdown", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/FileManager")== 0)
		{/*/usr/bin/FileManager*/
			launchApp_portable("/usr/bin/FileManager", "Filemanager");
		}
		else if(strcmp(argv[0],"/home/Marvell-MID/nfs/usr/bin/TS")== 0)
		{/*/home/Marvell-MID/nfs/usr/bin/TS??????*/
			launchApp_portable("/home/Marvell-MID/nfs/usr/bin/TS", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/EightyOne")== 0)
		{/*/usr/bin/EightyOne*/
			launchApp_portable("/usr/bin/EightyOne", "EightyOne");
		}
		else if(strcmp(argv[0],"/usr/bin/GiveMeFive")== 0)
		{/*/usr/bin/GiveMeFive*/
			launchApp_portable("/usr/bin/GiveMeFive", "GiveMeFive");
		}
		else if(strcmp(argv[0],"/usr/bin/FBReader")== 0)
		{/*/usr/bin/FBReader*/
			launchApp_portable("/usr/bin/FBReader", "FBReader.FBReader");
		}
		else if(strcmp(argv[0],"/usr/bin/stardict")== 0)
		{/*/usr/bin/stardict*/
			launchApp_portable("/usr/bin/stardict", "stardict.Stardict");
		}
		else if(strcmp(argv[0],"/usr/bin/Paint")== 0)
		{/*/usr/bin/Paint*/
			launchApp_portable("/usr/bin/Paint", "TuxPaint.TuxPaint.TuxPaint.TuxPaint");
		}
		else if(strcmp(argv[0],"/usr/bin/iceweasel")== 0)
		{/*/usr/bin/iceweasel??????????*/
			launchApp_portable("/usr/bin/iceweasel", "videoWinTitle");
		}
		else if(strcmp(argv[0],"/usr/bin/StartDateTime")== 0)
		{/*/usr/bin/StartDateTime*/
			launchApp_portable("/usr/bin/StartDateTime", "DateTime");
		}
		else if(strcmp(argv[0],"/usr/bin/PhotoViewer.sh")== 0)
		{/*/usr/bin/PhotoViewer.sh*/
			launchApp_portable("/usr/bin/PhotoViewer.sh", "Photo Viewer");
		}
		else
		{
			g_print("the application command %s doesn't exists***\n", appCmd);
			g_print("you can add the other applications here\n");
		}
		if (argv)
			g_strfreev (argv);
	}
	return 0;
}
/*get the number of windows exist*/
int getWindowCount(void)
{
	Display *disp;
	unsigned long client_list_size = 0;
	Window *win_list = NULL;
	int count = 0;
	if(! (disp = XOpenDisplay(NULL)))
	{
		fputs("Cannot open display.\n", stderr);
		return ;
	}
	if ((win_list = get_client_list(disp, &client_list_size)) == NULL)
	{
		g_print("cann't get the window list!*****\n");
		return -1; 
	}
	count = client_list_size / sizeof(Window);
	g_free(client_list);
	XCloseDisplay(disp);
	return count;
}

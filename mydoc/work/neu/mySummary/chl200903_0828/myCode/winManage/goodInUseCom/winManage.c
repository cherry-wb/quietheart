#include "winManage.h"
#define p_verbose(...) if (options.verbose) { \
    fprintf(stderr, __VA_ARGS__); \
}

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

static Window *get_client_list (Display *disp, unsigned long *size);
static int client_msg(Display *disp, Window win, char *msg, 
        unsigned long data0, unsigned long data1, 
        unsigned long data2, unsigned long data3,
        unsigned long data4);
static int list_desktops (Display *disp);
static gchar *get_output_str (gchar *str, gboolean is_utf8);
static int close_window (Display *disp, Window win);
static gchar *get_window_title (Display *disp, Window win);
static gchar *get_property (Display *disp, Window win, 
        Atom xa_prop_type, gchar *prop_name, unsigned long *size);


void init_charset (void)
{
    const gchar *charset; 
    gchar *lang = getenv("LANG") ? g_ascii_strup(getenv("LANG"), -1) : NULL; 
    gchar *lc_ctype = getenv("LC_CTYPE") ? g_ascii_strup(getenv("LC_CTYPE"), -1) : NULL;
    
    
    envir_utf8 = g_get_charset(&charset);

    
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
}




static int client_msg(Display *disp, Window win, char *msg, 
        unsigned long data0, unsigned long data1, 
        unsigned long data2, unsigned long data3,
        unsigned long data4) {
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



static gchar *get_property (Display *disp, Window win, 
        Atom xa_prop_type, gchar *prop_name, unsigned long *size)
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
        g_print("Cannot get %s property.\n", prop_name);
        return NULL;
    }
  
    if (xa_ret_type != xa_prop_type) {
		p_verbose("Invalid type of %s property.\n", prop_name);
        XFree(ret_prop);
        return NULL;
    }

    
    tmp_size = (ret_format / 8) * ret_nitems;
    
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


static int close_window (Display *disp, Window win)
{
    return client_msg(disp, win, "_NET_CLOSE_WINDOW", 
            0, 0, 0, 0, 0);
}



int list_windows (Display *disp)
{
    Window *client_list;
    unsigned long client_list_size;
    int i;
    int max_client_machine_len = 0;
    
#if MY_DEBUG_OUTPUT == 1
	g_print("before get_client_list******\n");
#endif
    if((client_list = get_client_list(disp, &client_list_size)) == NULL)
	{
        return EXIT_FAILURE; 
    } 
#if MY_DEBUG_OUTPUT == 1
	g_print("after get_client_list******\n");
#endif
    
    for(i = 0; i < client_list_size / sizeof(Window); i++)
	{
        gchar *client_machine;
        if ((client_machine = get_property(disp, client_list[i],
                XA_STRING, "WM_CLIENT_MACHINE", NULL))) {
            max_client_machine_len = strlen(client_machine);    
        }
        g_free(client_machine);
    }
    
    
    for (i = 0; i < client_list_size / sizeof(Window); i++)
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("before get_window_title**\n");
#endif
        gchar *title_utf8 = get_window_title(disp, client_list[i]); 
#if MY_DEBUG_OUTPUT == 1
		g_print("after get_window_title**\n");
#endif
        gchar *title_out = get_output_str(title_utf8, TRUE);
#if MY_DEBUG_OUTPUT == 1
		g_print(title_out);
		g_print("*******title_out is ok??\n");
#endif
        gchar *client_machine;
        gchar *class_out = get_window_class(disp, client_list[i]); 
        unsigned long *pid;
        unsigned long *desktop;
        int x, y, junkx, junky;
        unsigned int wwidth, wheight, bw, depth;
        Window junkroot;

        
        if ((desktop = (unsigned long *)get_property(disp, client_list[i],
                XA_CARDINAL, "_NET_WM_DESKTOP", NULL)) == NULL) {
            desktop = (unsigned long *)get_property(disp, client_list[i],
                    XA_CARDINAL, "_WIN_WORKSPACE", NULL);
        }

        
        client_machine = get_property(disp, client_list[i],
                XA_STRING, "WM_CLIENT_MACHINE", NULL);
       
        
        pid = (unsigned long *)get_property(disp, client_list[i],
                XA_CARDINAL, "_NET_WM_PID", NULL);

	    
      
        printf("0x%.8lx %2ld", client_list[i], 
                desktop ? (signed long)*desktop : 0);

		
        printf(" %-6lu", pid ? *pid : 0);
		
		printf(" %-20s ", class_out ? class_out : "N/A");
        printf(" %*s %s\n",
              max_client_machine_len,
              client_machine ? client_machine : "N/A",
              title_out ? title_out : "N/A"
		);
        g_free(title_utf8);
        g_free(title_out);
        g_free(desktop);
        g_free(client_machine);
        g_free(class_out);
        g_free(pid);
    }
    g_free(client_list);
   
    return EXIT_SUCCESS;
}


Window get_active_window(Display *disp)
{
    char *prop;
    unsigned long size;
    Window ret = (Window)0;
    
    prop = get_property(disp, DefaultRootWindow(disp), XA_WINDOW, 
                        "_NET_ACTIVE_WINDOW", &size);
    if (prop) {
        ret = *((Window*)prop);
        g_free(prop);
    }

    return(ret);
}


gchar *get_window_title (Display *disp, Window win)
{
    gchar *title_utf8;
    gchar *wm_name;
    gchar *net_wm_name;

    wm_name = get_property(disp, win, XA_STRING, "WM_NAME", NULL);
    net_wm_name = get_property(disp, win, 
            XInternAtom(disp, "UTF8_STRING", False), "_NET_WM_NAME", NULL);
#if MY_DEBUG_OUTPUT == 1
	g_print("wm_name is: %s ******",wm_name);
#endif
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
int close_win_by_title(gchar *title)
{
    Window *client_list;
    unsigned long client_list_size;
	int count;
    int i;
	Display *disp;

	setlocale(LC_ALL, "");
	init_charset();
	if (! (disp = XOpenDisplay(NULL)))
	{
		fputs("Cannot open display.\n", stderr);
		return 1;
	}
    if((client_list = get_client_list(disp, &client_list_size)) == NULL)
	{
        return EXIT_FAILURE; 
    } 

	count = client_list_size / sizeof(Window);
    for (i = 0; i < count; i++)
	{
        gchar *title_utf8 = get_window_title(disp, client_list[i]); 
        gchar *title_out = get_output_str(title_utf8, TRUE);

		if(g_strcasecmp(title, title_out) == 0)
		{
			close_window(disp, client_list[i]);
			break;
		}
        g_free(title_utf8);
        g_free(title_out);
    }
    g_free(client_list);
	XCloseDisplay(disp);

	if(i >= count)
	{
		return EXIT_SUCCESS;
	}
	else
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("cann't find the window with title:%s \n", title);
#endif
		return 1;
	}
}

gchar *get_title_by_window(Display *disp, Window win)
{
	gchar *title_utf8 = get_window_title(disp, win); 
#if MY_DEBUG_OUTPUT == 1
	g_print("after get_window_title**\n");
#endif
	gchar *title_out = get_output_str(title_utf8, TRUE);
#if MY_DEBUG_OUTPUT == 1
	g_print(title_out);
	g_print("*******title_out is ok??\n");
#endif
	g_free(title_utf8);
	return title_out;
}

gchar *get_window_class (Display *disp, Window win)
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
unsigned long get_pid_by_window(Display *disp, Window win)
{
	unsigned long *p;
	p = (unsigned long *)get_property(disp, win,
			XA_CARDINAL, "_NET_WM_PID", NULL);
	unsigned long pid = *p;
	g_free(p);
	return pid;
}
Window *get_window_list(Display *disp, int *count)
{
    Window *client_list;
    unsigned long client_list_size;
	setlocale(LC_ALL, "");
	init_charset();
    if((client_list = get_client_list(disp, &client_list_size)) == NULL)
	{
        return NULL; 
    } 

	if(count != NULL)
	{
		*count = client_list_size / sizeof(Window);
	}
	return client_list;
}

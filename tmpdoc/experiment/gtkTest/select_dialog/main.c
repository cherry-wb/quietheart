/* For testing propose use the local (not installed) glade file */
/* #define GLADE_FILE PACKAGE_DATA_DIR"/shutdown_pc/glade/shutdown_pc.glade" */




#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#define EVENT_MASKS (GDK_PROXIMITY_IN_MASK | \
		GDK_PROXIMITY_OUT_MASK | \
		GDK_BUTTON_MOTION_MASK | \
		GDK_BUTTON_PRESS_MASK | \
		GDK_BUTTON_RELEASE_MASK)
#define OPAQUE	0xffffffff
#define OPACITY	"_NET_WM_WINDOW_OPACITY"
const gchar *background_png = PACKAGE_DATA_DIR"/shutdown_pc/silver_shutdown_background_no_full_desktop.png";

const gchar *item_normal_imgs[] =
{
	PACKAGE_DATA_DIR"/shutdown_pc/silver_task_manager_norm.png",
	PACKAGE_DATA_DIR"/shutdown_pc/silver_restart_norm.png",
	PACKAGE_DATA_DIR"/shutdown_pc/silver_shutdown_norm.png",
	PACKAGE_DATA_DIR"/shutdown_pc/silver_standby_norm.png",
};

const gchar *item_enter_imgs[] =
{
	PACKAGE_DATA_DIR"/shutdown_pc/silver_task_manager_hi.png",
	PACKAGE_DATA_DIR"/shutdown_pc/silver_restart_hi.png",
	PACKAGE_DATA_DIR"/shutdown_pc/silver_shutdown_hi.png",
	PACKAGE_DATA_DIR"/shutdown_pc/silver_standby_hi.png",

};

gchar *item_labels[] =
{
	"重启",
	"待机",
	"关机",
	"取消",	
};

typedef struct
{
	GtkWidget *image;
	gint index;
}ITEM_IMG;

int get_lang()
{
	int flag = 0;
	char * lang = g_getenv("LANG");	
	if (!strncasecmp(lang,"zh",2))
	{
		flag = 0;
	}
	else if (!strncasecmp(lang,"en",2))
	{
		flag = 1;
	}
	else if (!strncasecmp(lang,"ja",2))
	{
		flag = 2;
	}
	return flag;
}
	
void item_enter(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	ITEM_IMG *item_img = (ITEM_IMG *)data;
	GtkImage *image = (GtkImage *)item_img->image;
	gint index = item_img->index;
	const gchar *img_file = item_enter_imgs[index];

	gtk_image_set_from_file(image, img_file);
}

void item_leave(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	ITEM_IMG *item_img = (ITEM_IMG *)data;
	GtkImage *image = (GtkImage *)item_img->image;
	gint index = item_img->index;
	const gchar *img_file = item_normal_imgs[index];

	gtk_image_set_from_file(image, img_file);
}

GList *item_list = NULL;

const gchar *dialog_icon_file = PACKAGE_DATA_DIR"/shutdown_pc/shutdown_dialog.png";
const gchar *dialog_text = "您确定要继续吗？";
const gchar *dialog_button_text[] = {"OK", "取消"};

void do_reboot();
void do_shutdown();

void dialog_ok(GtkWidget *widget, gpointer data)
{
	const gchar *title = (const gchar *)data;
	if(!g_strcasecmp(title, item_labels[2]))
		do_reboot();
	else if(!g_strcasecmp(title, item_labels[3]))
		do_shutdown();					

}

void dialog_cancel(GtkWidget *widget, gpointer data)
{
	GList *list;
	for(list = item_list; list; list = list->next)
	{
		ITEM_IMG *item = (ITEM_IMG *)list->data;
		free(item);
	}

	g_print("quit!\n");
	gtk_main_quit();
}

GtkWidget *make_dialog(const gchar *title, const gchar *icon_file)
{
	GtkWidget *dialog;
	GtkWidget *hbox_label;
	GtkWidget *hbox_button;
	GtkWidget *vbox;
	GtkWidget *label;
	GtkWidget *button;

	dialog = gtk_dialog_new();
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 5);
	gtk_window_set_title(GTK_WINDOW(dialog), title);
	gtk_window_set_icon_from_file(GTK_WINDOW(dialog), icon_file, NULL);
	gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);

	hbox_label = gtk_hbox_new(FALSE, 0);
	label = gtk_label_new(dialog_text);
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(hbox_label), label, FALSE, FALSE, 0);

	hbox_button = gtk_hbox_new(TRUE, 0);

	button = gtk_button_new_with_label(dialog_button_text[0]);
	gtk_widget_set_size_request(button, 70, 26);
	gtk_box_pack_start(GTK_BOX(hbox_button), button, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button), "clicked",
						G_CALLBACK(dialog_ok), (gpointer)title);

	button = gtk_button_new_with_label(dialog_button_text[1]);
	gtk_widget_set_size_request(button, 70, 26);
	gtk_box_pack_start(GTK_BOX(hbox_button), button, FALSE, FALSE, 5);
	gtk_window_set_focus(GTK_WINDOW(dialog), button);
	g_signal_connect(G_OBJECT(button), "clicked",
						G_CALLBACK(dialog_cancel), NULL);

	vbox = GTK_DIALOG(dialog)->vbox;
	gtk_box_pack_start(GTK_BOX(vbox), hbox_label, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(vbox), hbox_button, FALSE, FALSE, 0);


	return dialog;
}


enum ITEM_JOB {REBOOT,STANDBY, SHUTDOWN, CANCEL};

const gchar *cmd_path = "/bin/bash";

void task_manager()
{
	g_print("task_manager\n");
}

void standby()
{
	//1 gnome-power-cmd.sh suspend
	//2 pm-suspend
	//static const gchar *cmd[] = {"bash", "-c", "pm-suspend", NULL };
	static const gchar *cmd[] = {"bash", "-c", "suspend-btn-press", NULL };

	execv(cmd_path, cmd);
}

void reboot()
{
	GtkWidget *dialog;
	int lang = get_lang();
	
			dialog = make_dialog(item_labels[2], dialog_icon_file);	
	
	

	gtk_widget_show_all(dialog);
}

void do_reboot()
{
	g_print("reboot!\n");

	// const gchar *cmd[] = {"bash", "-c", "shutdown -r now", NULL };
	const gchar *cmd[] = {"bash", "-c", "reboot", NULL };
	execv(cmd_path, cmd);
}

void shutdown()
{
	GtkWidget *dialog;
	int lang = get_lang();
	
			dialog = make_dialog(item_labels[3], dialog_icon_file);	
	
	gtk_widget_show_all(dialog);
}

void do_shutdown()
{
	g_print("shutdown!\n");

	// const gchar *cmd[] = {"bash", "-c", "shutdown -h now", NULL };
	const gchar *cmd[] = {"bash", "-c", "shutdown -h now", NULL };
	execv(cmd_path, cmd);
}
void cancel()
{
	GList *list;

	for(list = item_list; list; list = list->next)
	{
		ITEM_IMG *item = (ITEM_IMG *)list->data;
		free(item);
	}

	g_print("quit!\n");
	gtk_main_quit();
}
void item_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	ITEM_IMG *item_img = (ITEM_IMG *)data;
	gint index = item_img->index;

	switch(index)
	{
	case REBOOT:
		do_reboot();
		break;
	case STANDBY:
		standby();
		break;
	case SHUTDOWN:
		do_shutdown();
		break;
	case CANCEL:
		cancel();
		break;
	}
}

const gint label_width = 117;
const gint label_height = 15;
const gint label_pos_y = 90;

GtkWidget *make_item(gint index)
{
	GtkWidget *fixed_item;
	GtkWidget *event_box;
	GtkWidget *image;
	GtkWidget *label;
	const gchar *img_file;
	GdkColor color1;
  	gdk_color_parse ("white", &color1);
	fixed_item = gtk_fixed_new();

	img_file = item_normal_imgs[index];
	image = gtk_image_new_from_file(img_file);
	gtk_widget_show(image);
	
	const gchar *text = item_labels[index];
	
	label = gtk_label_new(text);
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_widget_set_size_request(label, label_width, label_height);

	ITEM_IMG *item_img = (ITEM_IMG *)malloc(sizeof(ITEM_IMG));
	item_img->image = image;
	item_img->index = index;

	item_list = g_list_append(item_list, (gpointer)item_img);

	event_box = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(event_box), image);
	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event_box), FALSE);
	gtk_widget_show(event_box);
	g_signal_connect(G_OBJECT(event_box), "enter_notify_event",
						G_CALLBACK(item_enter), (gpointer)item_img);
	g_signal_connect(G_OBJECT(event_box), "leave_notify_event",
						G_CALLBACK(item_leave), (gpointer)item_img);

	g_signal_connect(G_OBJECT(event_box), "button_press_event",
						G_CALLBACK(item_press), (gpointer)item_img);


	gtk_fixed_put(GTK_FIXED(fixed_item), event_box, 0, 0);
	gtk_widget_set_size_request(label, 110, 40);
	gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color1);
	gtk_fixed_put(GTK_FIXED(fixed_item), label, 0, label_pos_y);
	gtk_widget_show_all(fixed_item);

	return fixed_item;
}


void destroy(GtkWidget *widget, gpointer data)
{
	GList *list;
	for(list = item_list; list; list = list->next)
	{
		ITEM_IMG *item = (ITEM_IMG *)list->data;
		free(item);
	}
	//gdk_pointer_ungrab (GDK_CURRENT_TIME);
	g_print("quit!\n");
	gtk_main_quit();
}

const gint item_pos_x[] = {13, 133, 253, 373};
const gint item_pos_y = 10+70;

void make_icon_area(GtkWidget *fixed_base)
{
	GtkWidget *fixed;
	GtkWidget *fixed_item;
	gint item_count;
	gint i;

	fixed = fixed_base;
	item_count = sizeof(item_normal_imgs) / sizeof(item_normal_imgs[0]);

	for(i = 0; i < item_count; ++i)
	{
		fixed_item = make_item(i);
		gtk_fixed_put(GTK_FIXED(fixed), fixed_item, item_pos_x[i], item_pos_y);
	}
}

void cancel_enter(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	g_print("cancel enter\n");
}

void cancel_leave(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	g_print("cancel leave\n");
}

void cancel_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	GList *list;

	for(list = item_list; list; list = list->next)
	{
		ITEM_IMG *item = (ITEM_IMG *)list->data;
		free(item);
	}

	g_print("quit!\n");
	gtk_main_quit();
}

const gchar *cancel_text = "取消";
const gint cancel_label_width = 117;
const gint cancel_label_height = 32;
const gint cancel_label_pos_x = 373;
const gint cancel_label_pos_y = 135;

void make_cancel_button(GtkWidget *fixed_base)
{
	GtkWidget *fixed;
	GtkWidget *event_box;
	GtkWidget *label;

	fixed = fixed_base;

	label = gtk_label_new(cancel_text);
	gtk_widget_set_size_request(label, cancel_label_width, cancel_label_height);
	gtk_widget_show(label);

	GdkColor white = {0, 65535, 65535, 65535};
	GtkRcStyle *rc_style = gtk_rc_style_new ();
	rc_style->fg[GTK_STATE_NORMAL] = white;
	rc_style->color_flags[GTK_STATE_NORMAL] |= GTK_RC_FG;
	gtk_widget_modify_style(label, rc_style);
	gtk_rc_style_unref(rc_style);

	event_box = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(event_box), label);
	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event_box), FALSE);
	gtk_widget_show(event_box);
	g_signal_connect(G_OBJECT(event_box), "enter_notify_event",
						G_CALLBACK(cancel_enter), NULL);
	g_signal_connect(G_OBJECT(event_box), "leave_notify_event",
						G_CALLBACK(cancel_leave), NULL);
	g_signal_connect(G_OBJECT(event_box), "button_press_event",
						G_CALLBACK(cancel_press), NULL);

	gtk_widget_show(event_box);
	gtk_fixed_put(GTK_FIXED(fixed), event_box, cancel_label_pos_x, cancel_label_pos_y);
}

const gint window_width = 500/*504*/;
const gint window_height = 288/*169*/;

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *image;
	GtkWidget *fixed;
	// GtkWidget *item;
	GtkWidget *mainWindow;
	GdkScreen*  scr;
	GdkBitmap *window_mask;
	GdkPixmap *pixmap;
	GdkBitmap *pixmap_mask;
	int lang = get_lang();
	switch(lang)
	{
		case 0:
			item_labels[0] = g_strdup_printf("重启");
			item_labels[1] = g_strdup_printf("待机");
			item_labels[2] = g_strdup_printf("关机");
			item_labels[3] = g_strdup_printf("取消");
		break;
		case 1:
			item_labels[0] = g_strdup_printf("Restart");
			item_labels[1] = g_strdup_printf("Stand By");
			item_labels[2] = g_strdup_printf("Turn off");
			item_labels[3] = g_strdup_printf("Cancel");
		break;
		case 2:
			item_labels[0] = g_strdup_printf("再起動");
			item_labels[1] = g_strdup_printf("スタンバイ");
			item_labels[2] = g_strdup_printf("電源を切る");
			item_labels[3] = g_strdup_printf("キャンセル");
		break;
	}
	gtk_init(&argc, &argv);
//----------------------------------------------
	mainWindow = gtk_window_new( GTK_WINDOW_POPUP);
	scr = gtk_window_get_screen( GTK_WINDOW( mainWindow));
   GdkColor white;
gdk_color_parse("#9c9c9c",&white);
gtk_widget_modify_bg(mainWindow,GTK_STATE_NORMAL,&white);	
	gtk_window_set_default_size( GTK_WINDOW( mainWindow), 
		gdk_screen_get_width( scr), 
		gdk_screen_get_height( scr));
//gtk_widget_set_size_request(mainWindow, window_width, window_height);
	gtk_window_fullscreen( GTK_WINDOW( mainWindow));
	gtk_widget_show_all( mainWindow);
	gtk_widget_realize(GTK_WIDGET(mainWindow));
	Display *xdpy = XOpenDisplay(getenv("DISPLAY"));
  	GdkWindow *gdkwin = GTK_WIDGET(mainWindow)->window;
  	Window xwin = GDK_WINDOW_XID(gdkwin);

  	unsigned int opacity = (unsigned int) (0.70 * OPAQUE);
  
  	XChangeProperty(xdpy, xwin, XInternAtom(xdpy, OPACITY, False), 
		    XA_CARDINAL, 32, PropModeReplace, 
		    (unsigned char *) &opacity, 1L);
  	// XSync(xdpy, False);
//----------------------------------------------
	window = gtk_window_new(GTK_WINDOW_POPUP);
	g_signal_connect(G_OBJECT(window), "destroy",
						G_CALLBACK(destroy), NULL);

	gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);
//gtk_widget_set_size_request(window, window_width, window_height);
	 //gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_move(GTK_WINDOW(window), 249,163);
	gtk_window_set_modal(window,FALSE);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_title (GTK_WINDOW (window),"CloseWindow");
	
	/*gdk_pointer_grab (window->window, FALSE,
			(GdkEventMask)EVENT_MASKS, 0,
			NULL,
			GDK_CURRENT_TIME);*/



	gdk_pixmap_create_from_xpm(window->window, &window_mask, NULL, background_png);
	gtk_widget_shape_combine_mask (window, window_mask, 0, 0);

 gtk_widget_realize(GTK_WIDGET(window));

  Display *xdpy2 = XOpenDisplay(getenv("DISPLAY"));
  GdkWindow *gdkwin2 = GTK_WIDGET(window)->window;
  Window xwin2 = GDK_WINDOW_XID(gdkwin2);

  unsigned int opacity2 = (unsigned int) (0.80 * OPAQUE);
  
  XChangeProperty(xdpy2, xwin2, XInternAtom(xdpy2, OPACITY, False), 
		    XA_CARDINAL, 32, PropModeReplace, 
		    (unsigned char *) &opacity2, 1L);
  
gtk_widget_show_all(window);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_widget_show(fixed);

	pixmap = gdk_pixmap_create_from_xpm(window->window, &pixmap_mask, NULL, background_png);
	image = gtk_image_new_from_pixmap(pixmap, pixmap_mask);
	gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
	gtk_widget_show(image);

	make_icon_area(fixed);

	//make_cancel_button(fixed);
	XSync(xdpy, False);XSync(xdpy2, False);
	gtk_main();

	return 0;
}
